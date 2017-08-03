#include "functions.h"
/*
Funkcja konwertuje obraz w skali szarosci do tablicy jednowymiarowej wiersz po wierszu
*/
void MatToVector (vector<short int> &array, Mat &image)

    {
        if (image.isContinuous())
            {
                array.assign(image.datastart, image.dataend);
            }
        else
            {
                for(int i=0; i<image.rows;i++)
                        {
                            array.insert(array.end(), image.ptr<uchar>(i), image.ptr<uchar>(i)+image.cols);
                        }
            }
    }


double Median (vector<short int> &array)

    {

        size_t n = array.size() /  2;
        nth_element(array.begin(), array.begin() + n, array.end());
        return array[n];

    }


double Average (vector<short int> &array)

    {
        double sum=0.0;
        for (unsigned int i=0; i<array.size(); i++)
            {
                sum += array[i];
            }
        return sum / array.size();
    }


double StandardDeviation (vector<short int> &array, double average)

    {
        double accum = 0.0;
        for(unsigned int i=0; i<array.size(); i++)
            {
                accum += (array[i]-average)/(array.size()-1)*(array[i]-average);
            }

        double stdev = sqrt(accum);
        return stdev;
    }


double TreshHold (double standard_deviation, double median)

    {

        return median + (5 * standard_deviation);

    }

///!!!! optymalizuj!!!!/////////
void Rectangle (Mat &image, vector<short int> bin_array, Point &left_up_corner, Point &right_down_corner, Point &rectangle_center)

    {
        unsigned int minrows = 0;
        unsigned int mincols = 0;
        unsigned int maxrows = image.rows;
        unsigned int maxcols = image.cols;
        for (unsigned int i=0; i<bin_array.size(); i++)
            {
                if(bin_array[i] == 255)
                    {
                        if((i/image.cols)<maxrows) maxrows=(i/image.cols);
                        if(i/image.cols>minrows) minrows=i/image.cols;
                        if(i%image.cols<maxcols) maxcols=i%image.cols;
                        if(i%image.cols>mincols) mincols=i%image.cols;
                    }
            }
        swap(minrows, maxrows);
        swap(mincols, maxcols);
        left_up_corner.x = mincols;
        left_up_corner.y = minrows;
        right_down_corner.x = maxcols;
        right_down_corner.y = maxrows;
        rectangle_center.x = left_up_corner.x + (maxcols-mincols)/2;
        rectangle_center.y = left_up_corner.y + (maxrows-minrows)/2;
        //cv::rectangle(image,left_up_corner,right_down_corner,Scalar(0,224,221),3);
    }
/* dostaje ona domyślnie plik ktory jest generowany przy pomocy skryptu o następujacej budowie
*   1.x cord of slit_center
*   2.y cord of slit_center
*   3.If user want to show images
*   4.If uset want to show in stdin centers coords
*
*/
void set_config (Configuration &config)
    {
        vector<string> tab_of_lines;
        fstream input;
        input.open (config.config_file_name.c_str());
        string delimiter="=";
        if(!input.good())
            {
                cout<<"I did not open the file"<<endl;
                return ;
            }
        string tmp;
        int i=0;
        while(!input.eof())
            {
                getline(input,tmp);
                tab_of_lines.push_back(tmp);
                i += 1;
            }
        tab_of_lines[0]=tab_of_lines[0].substr(tab_of_lines[0].find(delimiter)+1,tab_of_lines[0].length());
        tab_of_lines[1]=tab_of_lines[1].substr(tab_of_lines[1].find(delimiter)+1,tab_of_lines[1].length());
        config.x_slit_center=atoi(tab_of_lines[0].c_str());
        config.y_slit_center=atoi(tab_of_lines[1].c_str());

    }

/*
 *        Funkcja dostaje na wejsciu liczbę wywołania argumentów programu oraz tablicę z ich nazwami.
 *        Szuka ona opcji -C lub -c i  jeżeli następny argument istnieje i można go otworzyć
 *        ustawia docelowo jako nazwę pliku konfiguracyjnego. Jeżeli po opcji -c nie podamy nic lub nie wywołamy -c  lub plik configuracyjny
 *        nie istnieje wtedy ustawa defaultowe dane. Znaleziona nazwe pliku konfiguracyjnego zapisuje w klasie Configuration
 *
 */
void Search_Config(int argc, char* argv[], Configuration &config)
    {
        for (int i=1; i<argc; i++)
            {
                if(argv[i][0]=='-')
                    {
                        if(argv[i][1]=='C' || argv[i][1]=='c')
                            {
                                if(i<(argc-1) )
                                    {
                                        fstream try_input;
                                        try_input.open(argv[i+1]);
                                        if(try_input.good())
                                            {
                                                config.config_file_name=argv[i+1];
                                                //cout<<argv[i+1];

                                            }
                                    }
                            }
                        if(argv[i][1]=='M' || argv[i][1]=='m')
                            {
                                if(i < (argc-1))
                                    {
                                        config.metod=tolower(argv[i+1][0]);
                                    }
                                else
                                    {
                                        config.metod='a';
                                    }
                            }

                    }

            }
        return ;
    }
/*
 * Funkcja jako parametr otrzymuje nazwę pliku szuka ostatniej kropki i sprawdza czy napis jest identyczny z
 * najbardziej popularnymi formatami graficznymi*
 * */
bool IsPhoto (string file_name)
    {
        std::transform(file_name.begin(),file_name.end(),file_name.begin(),::tolower);
        file_name=file_name.substr(file_name.find_last_of(".") +1,file_name.length());
        if(file_name=="bmp" || file_name=="jpg" || file_name=="png" || file_name=="jpeg")
            return true;
        else
            return false;
    }
/*Funkcja dostaje na wejściu obiekt zdjęcie wkonuje na nim operację filtru medianowego, następnie konwetuje
 * w skalę szarości,nakłada filt gausowski,oraz wykonuje binaryzację i ponowny filtr medianowy, w kolejnych
 * etapach dane obrazu zapisuje do odpowiednich wektorow reprezentujących te obrazy
 */

int PhotoEditor (Picture &picture1, OutputData &output)

    {
        medianBlur(picture1.image,picture1.blurred_image,5);
        cvtColor(picture1.blurred_image,picture1.gray_image, CV_BGR2GRAY);
        GaussianBlur( picture1.gray_image,picture1.gray_image, Size( 5, 5), 3, 3 );
        MatToVector(picture1.gray_array,picture1.gray_image);
        picture1.average=Average(picture1.gray_array);
        picture1.median1=Median(picture1.gray_array);
        picture1.stdev1=StandardDeviation(picture1.gray_array,picture1.median1);
        picture1.th1=TreshHold(picture1.stdev1,picture1.median1);
        threshold(picture1.gray_image, picture1.bin_image, picture1.th1, 255 , THRESH_BINARY);
        medianBlur(picture1.bin_image,picture1.bin_image,7);
        MatToVector(picture1.bin_array,picture1.bin_image);
        Rectangle(picture1.image,picture1.bin_array,picture1.left_up_corner,picture1.right_down_corner,output.rectangle_center);
        int length = picture1.right_down_corner.x-picture1.left_up_corner.x;
        int hight = picture1.right_down_corner.y-picture1.left_up_corner.y;
        if(length<0 || hight < 0)
            {
                return -1;
            }
        else
            {
                Rect ROI(picture1.left_up_corner.x,picture1.left_up_corner.y,picture1.right_down_corner.x-picture1.left_up_corner.x,picture1.right_down_corner.y-picture1.left_up_corner.y);
                picture1.cuted_image=picture1.image(ROI);
                MatToVector(picture1.cuted_array,picture1.cuted_image);

            }
        return 0;

    }
void Hough_Center(Picture &picture1,OutputData &output)
    {
                    vector<Vec3f> circles;
                    HoughCircles(picture1.bin_image,circles,CV_HOUGH_GRADIENT,1,picture1.image.rows,200,5,15,3*(picture1.right_down_corner.x-picture1.left_up_corner.x)/2);

                    for(size_t i=0; i<circles.size(); i++)
                        {
                        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                        if(center.x<picture1.left_up_corner.x || center.x>picture1.right_down_corner.x ||
                            center.y<picture1.left_up_corner.y || center.y>picture1.right_down_corner.y)
                            {
                                break;
                            }
                        else
                            {
                                output.hough_center.x=center.x;
                                output.hough_center.y=center.y;
                                int radius=cvRound(circles[i][2]);
                                //circle( picture1.image, center, 1, Scalar(0,255,0), -1, 8, 0 );
                                //circle( picture1.image, center, radius, Scalar(0,0,255), 3, 8, 0 );
                            }
                        }
    }
ostream &operator<<(ostream &out, Picture &picture1)

    {
                namedWindow("Wykryte koło",CV_WINDOW_AUTOSIZE);

                namedWindow("Obraz binarny",CV_WINDOW_AUTOSIZE);

                imshow("Obraz binarny",picture1.bin_image);

                imshow("Wykryte koło",picture1.image);

                waitKey(0);

                return out;
    }

ostream &operator<<(ostream &out, OutputData &output)

    {
        if(output.hough_center.x==0 || output.hough_center.y==0)
            {
                out<<"Rectangle Center:"<<output.rectangle_center<<"Weighted Center:"<<output.weighted_center<<endl;
            }
        else
            {
                out<<"Hough Center:"<<output.hough_center<<"Rectangle Center:"<<output.rectangle_center<<"Weighted Center:"<<output.weighted_center<<endl;
            }
        return out;
    }

void WeightedCenter(Picture &picture1,OutputData &output)
        {
            float sum=accumulate(picture1.cuted_array.begin(),picture1.cuted_array.end(),0.0);
            float Mx=0.0;
            float My=0.0;

            for(int i=0;i<picture1.cuted_image.rows;i++)
                {
                    for(int j=0; j<picture1.cuted_image.cols;j++)
                        {

                            Mx += (picture1.cuted_array[(i*picture1.cuted_image.cols) + j]*j/sum);
                            My += (picture1.cuted_array[(i*picture1.cuted_image.cols) + j]*i/sum);
                        }

                }
                output.weighted_center.x += picture1.left_up_corner.x + Mx -1 ;
                output.weighted_center.y += picture1.left_up_corner.y + My-1;
                circle( picture1.image, output.weighted_center, 1, Scalar(255,20,147), -1, 8, 0 );
    }

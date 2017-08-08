#include "Includes.h"
#include "Picture.h"
#include "OutputData.h"
#include "Configuration.h"


/*
Funkcja konwertuje obraz w skali szarosci do tablicy jednowymiarowej wiersz po wierszu.
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

/*
    Obliczanie mediany z danych zawartych w wektorze z wykorzystaniem
    nth_element [#include <numeric>]. Nie sprawdzam parzystosci i nieparzystosci
    dlugosci wektora poniewaz mowiono ze i tak nie bd miec to kolosalnej roznicy
*/

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
                sum += array[i] / array.size();
            }
        return sum ;
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

        return median + (6 * standard_deviation);

    }

///!!!! optymalizuj!!!!/////////
Point Rectangle (Mat &image, vector<short int> bin_array, Point &left_up_corner, Point &right_down_corner, Point &result_center)

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
        result_center.x = left_up_corner.x + (maxcols-mincols)/2;
        result_center.y = left_up_corner.y + (maxrows-minrows)/2;
        return result_center;

    }
/* Funkcja z pliku konfiguracyjnego czyta współrzedne środka szczeliny
*  i zapisuje je do klasy przechowującej ustawienia programu.
*/
void set_config (Configuration &config)
    {
        vector<string> tab_of_lines;
        fstream input;
        input.open (config.config_file_name.c_str());
        string delimiter="=";
        if(!input.good())
            {
                cout<<"I did not open the configuration file"<<endl;
                return;
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
        config.slit_center.x=atoi(tab_of_lines[0].c_str());
        config.slit_center.y=atoi(tab_of_lines[1].c_str());
        cout<<"Slit data are downloaded from: "<<config.config_file_name.c_str()<<endl;
        return;
    }
/*
 *        Funkcja dostaje na wejsciu argc, tablice argv[], oraz klasę, zawierającą ustawienia programu:
 *        -c nazwa_pliku_configuracyjnego (w nim współrzędne środka szczeliny)
 *        -m (metoda obliczenia środka defaultowo jako średnia arytmetyczna)
 *        -e [float] (odleglość powyżej której stwierdzamy błąd i szukamy wektora translacji)
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
                        if(argv[i][1]=='E' || argv[i][1]=='e')
                            {
                                if(i < (argc-1))
                                    {
                                        config.error_treshold=atof(argv[i+1]);
                                    }
                                else
                                    {
                                        config.error_treshold=7.5;
                                    }
                            cout<<"You set up a error treshold to: "<<config.error_treshold<<endl;
                            }
                    }
            }
        return;
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
/*Funkcja dostaje na wejściu obiekt zdjęcie wkonuje na nim operację filtru medianowego, następnie konwertuje
 * w skalę szarości,nakłada filt gausowski,oraz wykonuje binaryzację i ponowny filtr medianowy, w kolejnych
 * etapach dane obrazu zapisuje do odpowiednich wektorow reprezentujących te obrazy
 */

int PhotoEditor (Picture &picture1, OutputData &output)

    {
        //medianBlur(picture1.image,picture1.blurred_image,3);
        cvtColor(picture1.image,picture1.gray_image, CV_BGR2GRAY);
        GaussianBlur( picture1.gray_image,picture1.gray_image, Size( 5, 5), 3, 3 );
        MatToVector(picture1.gray_array,picture1.gray_image);
        //picture1.average=Average(picture1.gray_array);
        //picture1.median1=Median(picture1.gray_array);
        picture1.median1=4;
        picture1.stdev1=StandardDeviation(picture1.gray_array,picture1.median1);
        picture1.th1=TreshHold(picture1.stdev1,picture1.median1);
        threshold(picture1.gray_image, picture1.bin_image, picture1.th1, 255 , THRESH_BINARY);
        medianBlur(picture1.bin_image,picture1.bin_image,7);
        MatToVector(picture1.bin_array,picture1.bin_image);
        output.result_center=Rectangle(picture1.image,picture1.bin_array,picture1.left_up_corner,picture1.right_down_corner,output.result_center);
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
Point Hough_Center(Picture &picture1,OutputData &output)

    {
        Point center;
        vector<Vec3f> circles;
        HoughCircles(picture1.bin_image,circles,CV_HOUGH_GRADIENT,1,picture1.image.rows,200,5,15,3*(picture1.right_down_corner.x-picture1.left_up_corner.x)/2);
        if(circles.size()==0)
            {
                return output.result_center;
            }
        center.x=circles[0][0];
        center.y=circles[0][1];
        if(center.x<picture1.left_up_corner.x || center.x>picture1.right_down_corner.x ||
        center.y<picture1.left_up_corner.y || center.y>picture1.right_down_corner.y)
            {
                return output.result_center;
            }
        return center;

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

Point WeightedCenter(Picture &picture1,OutputData &output)
        {
            Point weighted_center;
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
                weighted_center.x += picture1.left_up_corner.x + Mx -1 ;
                weighted_center.y += picture1.left_up_corner.y + My-1;
                circle(picture1.image, weighted_center, 1, Scalar(255,20,147), -1, 8, 0);
                return weighted_center;
    }

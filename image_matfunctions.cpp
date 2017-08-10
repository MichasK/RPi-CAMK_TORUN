#include "Includes.h"
#include "Picture.h"
#include "OutputData.h"
#include "Configuration.h"

double Median (vector<short int> &array)

    {

        size_t n = array.size() /  2;
        nth_element(array.begin(), array.begin() + n, array.end());
        return array[n];

    }


double Average (vector<short int> &array)

    {
        double sum=0.0;
        float dominator=array.size();
        for (unsigned int i=0; i<array.size(); i++)
            {
                sum += array[i] /dominator;
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




ostream &operator<<(ostream &out, Picture &picture1)

    {
                namedWindow("Wykryte koło",CV_WINDOW_AUTOSIZE);

                namedWindow("Obraz binarny",CV_WINDOW_AUTOSIZE);

                imshow("Obraz binarny",picture1.bin_image);

                imshow("Wykryte koło",picture1.image);

                waitKey(0);

                return out;
    }

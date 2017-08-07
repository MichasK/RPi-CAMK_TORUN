#include "Includes.h"
#include "Picture.h"
#include "OutputData.h"
#include "Configuration.h"
/*  1. Znalezienie pliku konfiguracyjnego.
    2. Ustawienie danych zawartych w pliku konfiguracyjnym
    3. Glowna petla programu dzialajaca dla wszystkich argumentow wywolania programu
    4. Sprawdzenie czy argument ma rozszerzenie charakterystyczne dla obrazow ?
    5. Funkcja PhotoEditor(-1, cos poszlo nie tak):
        a)filtr medianowy
        b)konwersja w skale szarosci
        c)filtr Gaussowski
        d)Przefiltrowany obraz -> gray_array
        e)Matematyczne obliczenia(srednia,mediana,odchylenie,threshold)
        f)binaryzacja obrazu pixele 0 || 255 -> bin_array.
    6. Transformacja Hougha.
    7. Obliczenie srodka wazonego.
*/
int main(int argc, char *argv[])
    {   int i=1;
        Configuration config;
        Search_Config(argc,argv,config);
        set_config(config);
        while(i < argc)
                {
                    Picture picture1;
                    OutputData output;
                    if(IsPhoto(argv[i]))
                        {
                        picture1.image=imread(argv[i],CV_LOAD_IMAGE_COLOR);
                         if(picture1.image.empty())
                            {
                                i += 1;
                                return -1;
                            }
                        if(PhotoEditor(picture1,output)==0)
                            {
                                if(config.metod=='h')
                                    {
                                        cout<<"Wybrales Hough_Center"<<endl;
                                        Hough_Center(picture1,output);
                                        output.vector_error = output.hough_center - config.slit_center;
                                        output.norm_of_vector_error = cv::norm(output.vector_error);

                                    }
                                if(config.metod=='w')
                                    {
                                        cout<<"Wybrales Srodek Wazony"<<endl;
                                        WeightedCenter(picture1,output);
                                        output.vector_error = output.weighted_center - config.slit_center;
                                        output.norm_of_vector_error = cv::norm(output.vector_error);

                                    }
                                if(config.metod=='r')
                                    {
                                        cout<<"Wybrales srodek prostokata"<<endl;
                                        output.vector_error = output.rectangle_center - config.slit_center;
                                        output.norm_of_vector_error = cv::norm(output.vector_error);

                                    }
                                if(config.metod=='a')
                                    {
                                        cout<<"Wybrales arytmetyczny"<<endl;
                                        WeightedCenter(picture1,output);
                                        Hough_Center(picture1,output);
                                        output.weighted_center = (output.weighted_center + output.rectangle_center + output.hough_center)/3;
                                        output.vector_error = output.weighted_center - config.slit_center;
                                        output.norm_of_vector_error = cv::norm(output.vector_error);
                                    }
                            }
                        }
                    i += 1;

                }
        return 0;
    }

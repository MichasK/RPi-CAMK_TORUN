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
    {
        Configuration config;
        Search_Config(argc,argv,config);
        set_config(config);
        int i=1;
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
                                        output.result_center=Hough_Center(picture1,output);

                                    }
                                if(config.metod=='w')
                                    {
                                        output.result_center=WeightedCenter(picture1,output);

                                    }
                                if(config.metod=='r')
                                    {
                                        //defaultowo ustawiony srodek to srodek prostokata
                                    }
                                if(config.metod=='a')
                                    {
                                        Point Hough=Hough_Center(picture1,output);
                                        Point Weighted=WeightedCenter(picture1,output);
                                        output.result_center += Weighted + Hough;
                                        output.result_center /= 3;
                                    }
                                    output.vector_error = output.result_center - config.slit_center;
                                    output.norm_of_vector_error = cv::norm(output.vector_error);
                                    cout<<output.result_center<<endl;
                            }
                        }
                    i += 1;
                    //cout<<picture1;
                }
        return 0;
    }

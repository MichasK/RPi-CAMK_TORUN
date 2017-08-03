#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "functions.h"
/*  1. Znalezienie pliku konfiguracyjnego.
    2. Ustawienie danych zawartych w pliku konfiguracyjnym, do klasy odpowiedzialnej za dzialanie programu
    3. Glowna petla programu dzialajaca dla wszystkich argumentow wywolania programu
    4. Sprawdzenie czy argument ma rozszerzenie charakterystyczne dla obrazow ?
    5. Funkcja PhotoEditor(-1, cos poszlo nie tak):
        a)Filt medianowy
        b)konwersja w skale szarosci
        c)filtr gausowski
        d) Przefiltrowany obraz -> gray_array
        e)Matematyczne obliczenia(srednia,mediana,odchylenie,threshold,liczba pixeli)
        f)binaryzacja obrazu pixele 0 || 255 -> bin_array.
        g) opcjonalnie filt medianowy ponownie na zbinaryzowanym obrazie.
        h)znajduje najmniejszy prostokat opisujacy plamke, wyciecie tego obrazu ->cuted_array
        i)znalezienie najjasniejszego punktu + pole plamki.
    6. Transformacja Hougha.
    7. Obliczenie srodka wazonego.
    8. Zapis danych do pliku.

////!!!
        /Circle Error do usupelnienia/
////!!!

*/

int main(int argc, char *argv[])
    {   int i=1;
        Configuration config;
        Search_Config(argc,argv,config);
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
                                        Hough_Center(picture1,output);
                                        cout<<output.hough_center;
                                        cout<<" Wybrales Hough_Center"<<endl;
                                    }
                                if(config.metod=='w')
                                {
                                    WeightedCenter(picture1,output);
                                    cout<<output.weighted_center;
                                    cout<<" Wybrales srodek wazony"<<endl;;
                                }
                                if(config.metod=='r')
                                    {
                                        cout<<output.rectangle_center;
                                        cout<<" Wybrales srodek prostokata"<<endl;
                                    }
                                if(config.metod=='a')
                                    {
                                        cout<<"Wbrales arytmetyczny"<<endl;
                                    }

                            }
                        }

                    i += 1;
                }

        return 0;
    }

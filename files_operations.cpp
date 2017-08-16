
/*/////////////////////////////////////////////////////
created by: Michał Krzyszczuk
date: July 2017
e-mail: krzyszczuk.michal@gmail.com
////////////////////////////////////////////////////*/
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Configuration.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
    /*
    Zapis lini do pliku, umożliwia podtrzymywanie dowolnej i stalej dlugosci pliku w liniach.
    Parametry wejsciowe
        string message              || linia zapisywana do pliku txt, trzeba uwazać aby napis był bez konca linii
        int lines_treshold          || maksymalna liczba linii w pliku
        string output_file_name     || ścieżka do pliku zapisu
    */
int SaveToFile (std::string message, int lines_treshold, std::string output_file_name)
        {
            std::fstream output_file;
            output_file.open(output_file_name.c_str(),std::ios::in);
            std::fstream temp_file;
            temp_file.open("temp_file.txt",std::ios::out | std::ios::app);
            std::string line;
            if(temp_file.bad() || output_file.bad())
                {
                    std::cout<<"I did not open the file in SaveToFile function";
                    return -1;
                }
            int line_counter=0;
            while(getline(output_file,line)) line_counter += 1;
            output_file.clear();
            output_file.seekg(0, std::ios::beg);
            temp_file<<message<<std::endl;
            if(line_counter<lines_treshold)
                {
                    while(getline(output_file,line))
                    temp_file<<line<<std::endl;
                }
            else
            {
                int i=0;
                while(i < lines_treshold-1)
                {
                    getline(output_file,line);
                    temp_file<<line<<std::endl;
                    i += 1;
                }
            }
            if(remove(output_file_name.c_str())!=0)
                {
                    std::cout<<"Deleting Error in SaveToFile function"<<std::endl;
                }
            rename("temp_file.txt",output_file_name.c_str());
            return 0;
        }


    /*
     * Funkcja jako parametr otrzymuje nazwę pliku szuka ostatniej kropki i sprawdza czy napis jest identyczny z
     * najbardziej popularnymi formatami graficznymi*
     * */
    bool IsPhoto (std::string &file_name)
        {
            std::transform(file_name.begin(),file_name.end(),file_name.begin(),::tolower);
            std::string file_extension = file_name.substr(file_name.find_last_of(".") +1,file_name.length());
            file_name = file_name.substr(file_name.find_last_of("/")+1,file_name.length());
            if(file_extension=="bmp" || file_extension=="jpg" || file_extension=="png" || file_extension=="jpeg")
                return true;
            else
                return false;
        }


        /* Funkcja z pliku konfiguracyjnego czyta współrzedne środka szczeliny
        *  i zapisuje je do klasy przechowującej ustawienia programu.
        */
void set_config (Configuration &config)
        {
            std::vector<std::string> tab_of_lines;
            std::fstream input;
            input.open (config.config_file_name.c_str());
            std::string delimiter="=";
            if(!input.good())
                {
                    std::cout<<"I did not open the configuration file"<<std::endl;
                    return;
                }
            std::string tmp;
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
                                            std::fstream try_input;
                                            try_input.open(argv[i+1]);
                                            if(try_input.good())
                                                {
                                                    config.config_file_name=argv[i+1];
                                                    //std::cout<<argv[i+1];
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
                                }
                        }
                }
            return;
        }

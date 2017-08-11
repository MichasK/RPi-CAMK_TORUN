/*/////////////////////////////////////////////////////
created by: Michał Krzyszczuk
date: July 2017
e-mail: krzysczuk.michal@gmail.com
////////////////////////////////////////////////////*/
#include "Includes.h"
#include <stdio.h>
/*
Zapis lini do pliku, umożliwia podtrzymywanie dowolnej i stalej dlugosci pliku w liniach.
Parametry wejsciowe
    string message              || linia zapisywana do pliku txt
    int lines_treshold          || maksymalna liczba linii w pliku
    string output_file_name     || ścieżka do pliku zapisu
*/
int SaveToFile (std::string message, int lines_treshold, std::string output_file_name)
    {
        std::fstream output_file;

        output_file.open(output_file_name,ios::in);
        std::fstream temp_file;
        temp_file.open("temp_file.txt",ios::out | ios::app);
        std::string line;
        if(temp_file.bad() || output_file.bad())
            {
                std::cout<<"I did not open the file in SaveToFile function";
                return -1;
            }
        int line_counter=0;
        while(getline(output_file,line)) line_counter += 1;
        output_file.clear();
        output_file.seekg(0, ios::beg);
        temp_file<<message<<std::endl;
        if(line_counter<lines_treshold)
            {
                while(getline(output_file,line))
                temp_file<<line<<endl;
            }
        else
        {
            int i=0;
            while(i < lines_treshold-1)
            {
                getline(output_file,line);
                temp_file<<line<<endl;
                i += 1;
            }
        }
        if(remove(output_file_name.c_str())!=0)
            {
                std::cout<<"Deleting Error in SaveToFile function"<<endl;
            }
        rename("temp_file.txt",output_file_name.c_str());
        return 0;
    }

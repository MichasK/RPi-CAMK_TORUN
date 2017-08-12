/*/////////////////////////////////////////////////////
created by: Michał Krzyszczuk
date: July 2017
e-mail: krzyszczuk.michal@gmail.com
////////////////////////////////////////////////////*/
#include "Includes.h"
#include "Picture.h"
#include "OutputData.h"
#include "Configuration.h"
#include "image_processing.h"
#include "image_matfunctions.h"
#include <unistd.h> /*for UART*/
#include <fcntl.h> /*for UART*/
#include <termios.h> /*for UART*/
#include "files_operations.h"
extern "C"{
#include "uart.h"
};
#include <iomanip>
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
    int uart_filestream = uart_init();//nie przetestowane
    Configuration config;
    Search_Config(argc,argv,config);
    set_config(config);
    Picture picture;
    OutputData output;
    stringstream result_line;
    string file_output_line;
    int i = 1;
    while(i < argc)
        {
            string path_to_file(argv[i]);
            picture.image=imread(argv[i],CV_LOAD_IMAGE_COLOR);
            if(IsPhoto(path_to_file) && ~picture.image.empty())
                {
                //cout<<path_to_file<<endl;
                if(PhotoEditor(picture,output)==0)
                    {
                        result_line<<setw(5)<<left<<cv::norm(output.result_center-config.slit_center);
                        result_line<<'\t'<<'\t';
                        Point Hough=Hough_Center(picture,output);
                        result_line <<setw(5)<<left<<cv::norm(Hough-config.slit_center);
                        result_line<<'\t'<<'\t';
                        Point Weighted=WeightedCenter(picture,output);
                        result_line<<setw(5)<<left<<cv::norm(Weighted-config.slit_center);
                        result_line<<'\t'<<'\t';
                        output.result_center += Weighted + Hough;
                        output.result_center /= 3;
                        result_line <<setw(5)<<left<<cv::norm(output.result_center-config.slit_center);
                    }
                output.vector_error = output.result_center - config.slit_center;
                output.norm_of_vector_error = cv::norm(output.vector_error);
                if(output.norm_of_vector_error >= config.error_treshold) write(uart_filestream,"1\n",2);
                else
                    {
                        write(uart_filestream,"3\n",2);
                        SaveToFile(GetActualTime(),5,"html/error_list.txt");
                    }
                SaveToFile(result_line.str(),100,"html/ErrorVectorNorm.txt");
                result_line.str(std::string());
                }
                i += 1;
        }
    close(uart_filestream);
    return 0;
}

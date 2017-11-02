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
extern "C" {
#include "uart.h"
};
#include <iomanip>
/*
 */
int main(int argc, char *argv[])
{
	int uart_filestream= uart_init();
	Configuration	config;
	Search_Config(argc, argv, config);
	set_config(config);
	Picture frame;
	OutputData output;
	stringstream result_line; //zapis wszystkich dlugosci wektorow do pliku
	int i = 1;
	while (i < argc) {
		string path_to_file(argv[i]);
		frame.image = imread(argv[i], CV_LOAD_IMAGE_COLOR);
		if (IsPhoto(path_to_file) && ~frame.image.empty()) //jezeli cos jest obrazem i zostalo wczytane
				{

			if (PhotoEditor(frame, output) == 0) {
				result_line << setw(5) << left
						<< cv::norm(output.result_center - config.slit_center);
				result_line << '\t' << '\t';
				Point Hough = Hough_Center(frame, output);
				result_line << setw(5) << left
						<< cv::norm(Hough - config.slit_center);
				result_line << '\t' << '\t';
				Point Weighted = WeightedCenter(frame, output);
				result_line << setw(5) << left
						<< cv::norm(Weighted - config.slit_center);
				result_line << '\t' << '\t';
				output.result_center += Weighted + Hough;
				output.result_center /= 3;
				result_line << setw(5) << left
						<< cv::norm(output.result_center - config.slit_center);
			}
			output.vector_error = output.result_center - config.slit_center;
			output.norm_of_vector_error = cv::norm(output.vector_error);
			if (output.norm_of_vector_error >= config.error_treshold)
				continue; //write(uart_filestream,"1\n",2);
			else {
				//write(uart_filestream,"3\n",2);
				SaveToFile(GetActualTime(), 10, "/var/www/html/error_list.txt");
			}
			SaveToFile(result_line.str(), 100,
					"/var/www/html/ErrorVectorNorm.txt");
			result_line.str(std::string());
		}
		i += 1;
	}
	//close(uart_filestream);
	return 0;
}

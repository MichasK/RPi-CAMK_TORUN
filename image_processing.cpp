#include "Picture.h"
#include "OutputData.h"
#include "image_processing.h"
#include "image_matfunctions.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <numeric>
/*
 Funkcja otrzymuje Obraz w którym zawarta jest gwiazda i oblicza środek ważony wartości obrazu.
 weighted_center.x=picture[x][y]*x/sum
 weighted_center.y=picture[x][y]*y/sum
 Następnie dokonuje się kalibracji względem współrzednych na ramce
 Funkcja zwraca cv::Point będący współrzednymi srodka wazonego na obrazie
 */
cv::Point WeightedCenter(Picture &picture, OutputData &output)

{
	Point weighted_center;
	float sum = std::accumulate(picture.cuted_array.begin(),
			picture.cuted_array.end(), 0.0);
	float Mx = 0.0;
	float My = 0.0;
	for (int i = 0; i < picture.cuted_image.rows; i++) {
		for (int j = 0; j < picture.cuted_image.cols; j++) {
			Mx += (picture.cuted_array[(i * picture.cuted_image.cols) + j] * j
					/ sum);
			My += (picture.cuted_array[(i * picture.cuted_image.cols) + j] * i
					/ sum);
		}
	}
	weighted_center.x += picture.left_up_corner.x + Mx - 1;
	weighted_center.y += picture.left_up_corner.y + My - 1;
	return weighted_center;
}

/*  Funkcja poszukuje środka gwiazdy metoda Transformacji Hougha
 *   Zwraca
 *        a)punkt będący środkiem znalezionego okręgu
 *        b)środek prostokąta opisującego jeśli nie znaleziono
 */

cv::Point Hough_Center(Picture &picture, OutputData &output)

{
	Point center;
	std::vector<Vec3f> circles;
	HoughCircles(picture.bin_image, circles, CV_HOUGH_GRADIENT, 1,
			picture.image.rows, 200, 5, 0, 0);
	if (circles.size() == 0)
		return output.result_center;
	center.x = circles[0][0];
	center.y = circles[0][1];
	if (center.x < picture.left_up_corner.x
			|| center.x > picture.right_down_corner.x
			|| center.y < picture.left_up_corner.y
			|| center.y > picture.right_down_corner.y) {
		return output.result_center;
	}
	return center;

}
/*
 *   1)Filr Medianowy z maską 3x3
 *   2)Konwersja obrazu w skalę szarości
 *   3)Filr Gaussowski
 *   4)Obraz -> gray_array
 *   5)Operacja TreshHold -> bin_array
 *   6)Srodek prostokąta opisującego plamkę światła
 *   return
 jeżeli operacje zostały wykonane poprawnie 0;
 jeżeli nastąpi błąd -1;
 */
int PhotoEditor(Picture &picture, OutputData &output)

{
	Mat image_blurred;
	medianBlur(picture.image, image_blurred, 3);
	cvtColor(image_blurred, picture.image, CV_BGR2GRAY);
	GaussianBlur(picture.image, picture.image, Size(5, 5), 3, 3);
	MatToVector(picture.gray_array, picture.image);
	picture.median1 = Average(picture.gray_array);
	picture.stdev1 = StandardDeviation(picture.gray_array, picture.median1);
	picture.th1 = TreshHold(picture.stdev1, picture.median1);
	threshold(picture.image, picture.bin_image, picture.th1, 255,
			THRESH_BINARY);
	MatToVector(picture.bin_array, picture.bin_image);
	output.result_center = Rectangle(picture.image, picture.bin_array,
			picture.left_up_corner, picture.right_down_corner,
			output.result_center);
	int length = picture.right_down_corner.x - picture.left_up_corner.x;
	int hight = picture.right_down_corner.y - picture.left_up_corner.y;
	if (length < 0 || hight < 0)
		return -1;
	else {
		Rect ROI(picture.left_up_corner.x, picture.left_up_corner.y,
				picture.right_down_corner.x - picture.left_up_corner.x,
				picture.right_down_corner.y - picture.left_up_corner.y);
		picture.cuted_image = picture.image(ROI);
		MatToVector(picture.cuted_array, picture.cuted_image);
	}
	return 0;

}
/* Funkcja szuka prostokąta opisującego gwiazdę, zaimplementowana metoda do wykonania tej operacji potrzebuje przejść 1 raz
 * całą tablicę, jednak kilka razy musi nałożyć maskę ( dokładnie tyle razy ile mamy białych pikseli), jednak w porównianiu
 *do drugiej metody potrzebującej około 1.5 raza na przejscie tablicy i tak na próbie 1000 zdjec wypada lepiej więc ostatecznie ona została
 *uznana za najbardziej wydajna.
 */

Point Rectangle(Mat &image, std::vector<short int> bin_array,
		Point &left_up_corner, Point &right_down_corner, Point &result_center)

		{
	unsigned int minrows = 0;
	unsigned int mincols = 0;
	unsigned int maxrows = image.rows;
	unsigned int maxcols = image.cols;
	//int minrows1,mincols1,maxrows1,maxcols1;
	for (unsigned int i = 0; i < bin_array.size(); i++) {
		if (bin_array[i] == 255) {
			if ((i / image.cols) < maxrows)
				maxrows = (i / image.cols);
			if (i / image.cols > minrows)
				minrows = i / image.cols;
			if (i % image.cols < maxcols)
				maxcols = i % image.cols;
			if (i % image.cols > mincols)
				mincols = i % image.cols;
		}
	}
	swap(minrows, maxrows);
	swap(mincols, maxcols);
	/*for (int i=0; i< image.rows; i++)
	 {
	 for (int j=0; j<image.cols; j++)
	 {
	 if(bin_array[i*image.cols + j]  == 255)
	 {minrows = i;i=image.rows+1;j=image.cols+1;break;}
	 }
	 }
	 for (int j=0; j<image.cols; j++)
	 {
	 for(int i=0; i<image.rows; i++)
	 {
	 if(bin_array[i*image.cols + j]  == 255)
	 {mincols = j;i=image.rows+1;j=image.cols+1;break;}
	 }
	 }
	 for(int i=image.rows-1; i>=0; i--)
	 {
	 for(int j=0; j< image.cols; j++)
	 {
	 if(bin_array[i*image.cols + j]  == 255)
	 {maxrows = i;i=-1;j=image.cols+1;break;}
	 }
	 }
	 for(int j=image.cols-1; j>=0; j--)
	 {
	 for(int i=0; i<image.rows; i++)
	 {
	 if(bin_array[i*image.cols + j]  == 255)
	 {maxcols = j;i=image.rows+1;j=-1;break;}
	 }
	 }*/
	left_up_corner.x = mincols;
	left_up_corner.y = minrows;
	right_down_corner.x = maxcols;
	right_down_corner.y = maxrows;
	result_center.x = left_up_corner.x + (maxcols - mincols) / 2;
	result_center.y = left_up_corner.y + (maxrows - minrows) / 2;
	return result_center;

}

/*
 *    Funkcja konwertuje obraz w skali szarosci do tablicy jednowymiarowej wiersz po wierszu.
 */

void MatToVector(std::vector<short int> &array, Mat &image)

{
	if (image.isContinuous()) {
		array.assign(image.datastart, image.dataend);
	} else {
		for (int i = 0; i < image.rows; i++) {
			array.insert(array.end(), image.ptr<uchar>(i),
					image.ptr<uchar>(i) + image.cols);
		}
	}
}

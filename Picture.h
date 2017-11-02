#ifndef Picture_h
#define Picture_h

#include <opencv/cv.hpp>
#include <vector>
#include "OutputData.h"
using namespace cv;
class Picture {
private:
	cv::Point left_up_corner;
	cv::Point right_down_corner;
	cv::Mat bin_image;
	cv::Mat cuted_image;
	float median1;
	float stdev1;
	float th1;
	float average;
	std::vector<short int> gray_array;
	std::vector<short int> bin_array;
	std::vector<short int> cuted_array;
	std::vector<short int> mask_array;
public:
	cv::Mat image;
	std::string file_name;
	friend std::ostream &operator<<(std::ostream &out, Picture &picture1);
	friend double Median(std::vector<short int> &);
	friend double Average(std::vector<short int> &);
	friend double StandardDeviation(std::vector<short int> &, double);
	friend double TreshHold(double, double);
	friend Point Hough_Center(Picture &picture1, OutputData &output);
	friend int PhotoEditor(Picture &picture1, OutputData &output);
	friend void Rectangle(Picture &picture1, std::vector<int> bin_array,
			cv::Point &result_center);
	friend Point WeightedCenter(Picture &picture1, OutputData &output);
};

#endif

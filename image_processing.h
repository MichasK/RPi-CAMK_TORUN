#ifndef image_processing_h
#define image_processing_h
void MatToVector(std::vector<short int> &array, cv::Mat &image);
Point Rectangle(cv::Mat &image, std::vector<short int> bin_array,
		cv::Point &left_up_corner, cv::Point &right_down_corner,
		cv::Point &result_center);
int PhotoEditor(Picture &picture1, OutputData &output);
Point Hough_Center(Picture &picture1, OutputData &output);
Point WeightedCenter(Picture &picture1, OutputData &output);
#endif

#ifndef image_processing_h
#define image_processing_h
    void MatToVector (vector<short int> &array, Mat &image);
    Point Rectangle (Mat &image, vector<short int> bin_array, Point &left_up_corner, Point &right_down_corner, Point &result_center);
    int PhotoEditor (Picture &picture1, OutputData &output);
    Point Hough_Center(Picture &picture1,OutputData &output);
    Point WeightedCenter(Picture &picture1,OutputData &output);
#endif

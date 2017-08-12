#ifndef Picture_h
#define Picture_h

#include <opencv/cv.hpp>
#include <vector>
    using namespace cv;
class Picture
    {
    private:
        Point left_up_corner;
        Point right_down_corner;
        Mat bin_image;
        Mat cuted_image;
        float median1;
        float stdev1;
        float th1;
        float average;
        vector<short int> gray_array;
        vector<short int> bin_array;
        vector<short int> cuted_array;
        vector<short int> mask_array;
    public:
        Mat image;
        string file_name;
        friend ostream &operator<<(ostream &out, Picture &picture1);
        friend double Median(vector<short int> &);
        friend double Average(vector<short int> &);
        friend double StandardDeviation(vector<short int> &, double);
        friend double TreshHold(double, double);
        friend Point Hough_Center(Picture &picture1,OutputData &output);
        friend int PhotoEditor(Picture &picture1,OutputData &output);
        friend void Rectangle(Picture &picture1,vector<int> bin_array,Point &result_center);
        friend Point WeightedCenter(Picture &picture1,OutputData &output);
    };
    
#endif

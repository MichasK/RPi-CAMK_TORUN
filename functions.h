#ifndef functions_h
#define functions_h
    #include "opencv2/highgui/highgui.hpp"
    #include "opencv2/imgproc/imgproc.hpp"
    #include <opencv/cv.hpp>
    #include <iostream>
    #include <vector>
    #include <math.h>
    #include <numeric>
    #include <fstream>

    using namespace std;
    using namespace cv;
    class OutputData;
    class Picture;
    class Configuration;
    class Picture
        {
        private:
            Point left_up_corner;
            Point right_down_corner;
            Point the_brightness_point_cord;
            Mat blurred_image;
            Mat gray_image;
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
            friend void Hough_Center(Picture &picture1,OutputData &output);
            friend int PhotoEditor(Picture &picture1,OutputData &output);
            friend void Rectangle(Picture &picture1,vector<int> bin_array,Point &rectangle_center);
            friend void WeightedCenter(Picture &picture1,OutputData &output);
            friend void LightSpotField(Picture &picture1);

        };
class OutputData
    {
    public:
        Point hough_center;
        Point rectangle_center;
        Point weighted_center;
    public:
        friend ostream &operator<<(ostream &out, OutputData &output);
        friend void Rectangle(Mat &image,Point &left_up_corner, Point &right_down_corner,Point &rectangle_center);
        friend int PhotoEditor(Picture &picture1,OutputData &output);
        friend void Hough_Center(Picture &picture1,OutputData &output);
        friend void WeightedCenter(Picture &picture1,OutputData &output);
        friend void RPiPrintf(OutputData output, Configuration config);
    };
class Configuration
    {
    public:
        string config_file_name;
        int x_slit_center;
        int y_slit_center;
        char metod;//w-weighted , h-houghtransform , r-rectanglecenter, a-default srednia z wszystkich
        void set_config(Configuration &config);
    };
class DescribingRectangle

    {
    private:
        Point left_up_corner;
        Point right_down_corner;
        float diagonal;

    };
bool IsPhoto(string file_name);
void Search_Config(int argc,char* argv[],Configuration &config);
#endif

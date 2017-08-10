#ifndef functions_h
#define functions_h
    #include "opencv2/highgui/highgui.hpp"
    #include "opencv2/imgproc/imgproc.hpp"
    #include <opencv/cv.hpp>
    #include <iostream>
    #include <vector>
    #include <math.h>//stdev
    #include <numeric>//for nth_element
    #include <fstream>//for configuration_file

    class Configuration;
    class OutputData;
    class Picture;


    using namespace std;
    

    bool IsPhoto(string file_name);
    void Search_Config(int argc,char* argv[],Configuration &config);
    void set_config(Configuration &config);
#endif

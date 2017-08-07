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
    /*#include "Includes.h"
    #include "Picture.h"
    #include "OutputData.h"
    #include "Configuration.h"*/
    class Configuration;
    class OutputData;
    class Picture;
    using namespace std;
    using namespace cv;

    bool IsPhoto(string file_name);
    void Search_Config(int argc,char* argv[],Configuration &config);
    void set_config(Configuration &config);
#endif

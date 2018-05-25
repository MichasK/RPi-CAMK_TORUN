#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "src/SearchingMethods.hpp"

#include <iostream>

#include "src/Frame.hpp"
#include "src/AstronomicFrame.hpp"
#include "gtest/gtest.h"

int main( int argc, char** argv )
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    AstronomicFrame f("/home/michal/CLionProjects/SlitGuide/Frames/GuideFrame_2015_03_10_18_09_02.bmp");
    std::function<cv::Point(AstronomicFrame)> calculate=RectangleCenter;
    cv::Point a = calculateGuideCenter(f,calculate);
    
    
    return 0;
}

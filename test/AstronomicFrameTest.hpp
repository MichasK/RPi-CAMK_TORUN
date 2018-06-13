//
// Created by michal on 13.06.18.
//

#ifndef SLITGUIDE_ASTRONOMICFRAMETEST_HPP
#define SLITGUIDE_ASTRONOMICFRAMETEST_HPP
#include "gtest/gtest.h"
#include "AstronomicFrame.hpp"
class AstronomicFrameTest:public  ::testing::Test{
protected:
    virtual void SetUp(){
        Z = cv::Mat::eye(4,4, CV_8UC1);
    }
    cv::Mat Z;
    std::vector<uchar> correctVector{1,2,1,3,4,2,1,2};// stdev = 1.0690 mean=2
    std::vector<uchar> badVector{1,255};

};
#endif //SLITGUIDE_ASTRONOMICFRAMETEST_HPP

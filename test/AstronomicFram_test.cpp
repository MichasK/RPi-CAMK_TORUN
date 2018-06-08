//
// Created by michal on 06.03.18.
//

#include "AstronomicFram_test.hpp"
#include "gtest/gtest.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <numeric>

/*
TEST_F(AstoFrameTest,CalculateTreshold){
    ASSERT_NE(vecFrame.size(),0);
    auto n = vecFrame.size()/2;
    std::nth_element(vecFrame.begin(), vecFrame.begin()+n, vecFrame.end());
    double median = vecFrame[n];
    double mean = std::accumulate(vecFrame.begin(),vecFrame.end(),0.0)/vecFrame.size();
    EXPECT_LE(abs(mean-median),0.5);
}*/

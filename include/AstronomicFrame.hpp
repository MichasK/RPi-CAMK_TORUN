//
// Created by michal on 06.03.18.
//

#ifndef SLITGUIDE_ASTRONOMICFRAME_HPP
#define SLITGUIDE_ASTRONOMICFRAME_HPP
#include "Frame.hpp"

#include <opencv/cv.hpp>
const cv::Point LEFT_UP_SLIT_CORD(240, 249);
const cv::Point RIGHT_DOWN_SLIT_CORD(248,279);


namespace Astronomic{
class AstronomicFrame:public Frame{
private:

public:
    AstronomicFrame(std::string s):Frame(s){};
    AstronomicFrame(cv::Mat m):Frame(m){};
    cv::Mat ToBinary();



};
    double calcTreshold(const std::vector<uchar>&,float);
    cv::Mat addSlitMask(const cv::Mat&);
    AstronomicFrame fillFrame(const cv::Mat);
}

#endif //SLITGUIDE_ASTRONOMICFRAME_HPP

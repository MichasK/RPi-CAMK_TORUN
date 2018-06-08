//
// Created by michal on 06.03.18.
//

#ifndef SLITGUIDE_ASTRONOMICFRAME_HPP
#define SLITGUIDE_ASTRONOMICFRAME_HPP
#include "Frame.hpp"

#include <opencv/cv.hpp>
const int X_SLIT_CENTER_CORD = 241;
const int Y_SLIT_CENTER_CORD = 250;
const int VERTICAL_SIZE = 30;
const int HORIZONTAL_SIZE =15;

namespace AstronomicFrame{
class AstronomicFrame:public Frame{
private:

public:
    AstronomicFrame(std::string s):Frame(s){};
    AstronomicFrame(cv::Mat m):Frame(m){};
    void filtrFrame();


};
    double calcTreshold(const std::vector<uchar>&,float);
    void addSlitMask(cv::Mat&);
}

#endif //SLITGUIDE_ASTRONOMICFRAME_HPP

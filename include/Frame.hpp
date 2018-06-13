//
// Created by michal on 05.03.18.
//

#ifndef SLITGUIDE_FRAME_HPP
#define SLITGUIDE_FRAME_HPP

#include <opencv/cv.hpp>

#include <vector>
#include <string>
#include <exception>
typedef std::vector<int> row;
typedef std::vector<row> Matrix;

class Frame{
protected:
    cv::Mat data;
    std::string frameName;
public:
    Frame(std::string);
    Frame(cv::Mat m): data(m){};
    Frame(){throw std::invalid_argument("Empty data must not be created");}
    cv::Mat getFrame()const{ return data;};
};
#endif //SLITGUIDE_FRAME_HPP

//
// Created by michal on 05.03.18.
//


#include "../include/Frame.hpp"
#include <iostream>

Frame::Frame(std::string pathToFile):frameName(pathToFile) {
    data = cv::imread(pathToFile.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
    if (data.empty()) {
        throw std::runtime_error("Unable to load data");
    }
}

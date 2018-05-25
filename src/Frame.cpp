//
// Created by michal on 05.03.18.
//

#include "Frame.hpp"
#include <iostream>

Frame::Frame(std::string pathToFile):frameName(pathToFile) {
    frame = cv::imread(pathToFile.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
    if (frame.empty()) {
        throw std::runtime_error("Unable to load frame");
    }
}

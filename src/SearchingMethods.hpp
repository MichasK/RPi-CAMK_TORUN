//
// Created by michal on 14.03.18.
//

#ifndef SLITGUIDE_SEARCHINGMETHODS_HPP
#define SLITGUIDE_SEARCHINGMETHODS_HPP
#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>
#include "AstronomicFrame.hpp"

cv::Point RectangleCenter(const AstronomicFrame &);
cv::Point HoughCenter(const AstronomicFrame &);
cv::Point HistogramCenter(const AstronomicFrame &);

#endif //SLITGUIDE_SEARCHINGMETHODS_HPP

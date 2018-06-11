//
// Created by michal on 11.06.18.
//

#ifndef SLITGUIDE_CENTERSEARCHINGMETHODS_HPP
#define SLITGUIDE_CENTERSEARCHINGMETHODS_HPP

#include <opencv2/core/types.hpp>

namespace CenterSearchingMethods{
    cv::Point HoughCenter(const cv::Mat&);
    cv::Point MinimumBoundignRectangleCenter(const cv::Mat &);
}
#endif //SLITGUIDE_CENTERSEARCHINGMETHODS_HPP

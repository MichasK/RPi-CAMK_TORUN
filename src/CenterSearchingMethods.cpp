//
// Created by michal on 11.06.18.
//

#include <opencv2/imgproc/types_c.h>
#include <opencv/cv.hpp>
#include "CenterSearchingMethods.hpp"

#include <exception>
#include <iostream>

namespace CenterSearchingMethods {

    cv::Point HoughCenter(const cv::Mat &filledFrame) {

        std::vector<cv::Vec3f> detected_circles;

        /// Apply the Hough Transform to find the circles
        cv::HoughCircles(filledFrame, detected_circles, CV_HOUGH_GRADIENT, 1, filledFrame.rows / 8, 200, 10, 0, 0);
        auto detected_circles_number = detected_circles.size();
        if (detected_circles_number == 0) {
            throw std::range_error("HoughCenter() not found.");
        } else if (detected_circles_number > 1) {
            throw std::range_error("HoughCenter() found many centers" + std::to_string(detected_circles_number));
        } else {
            for (size_t i = 0; i < detected_circles.size(); i++) {
                cv::Point center(cvRound(detected_circles[i][0]), cvRound(detected_circles[i][1]));
                int radius = cvRound(detected_circles[i][2]);
                // circle center
                circle(filledFrame, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
                // circle outline
                circle(filledFrame, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
            }
            return cv::Point(detected_circles[0][0], detected_circles[0][1]);
        }
    }


    cv::Point MinimumBoundignRectangleCenter(const cv::Mat &filledFrame) {
        bool STOP_LOOP_FLAG = 0;
        int up_border = 0;
        int left_border = 0;
        int down_border = 0;
        int right_border = 0;
        for (auto i = 0; i < filledFrame.rows; i++) {
            for (auto j = 0; j < filledFrame.cols; j++) {
                if (filledFrame.at<uchar>(i, j) == 255) {
                    up_border = i;
                    STOP_LOOP_FLAG = 1;
                    break;
                }
            }
            if (STOP_LOOP_FLAG) {
                STOP_LOOP_FLAG = 0;
                break;
            }
        }
        for (auto j = 0; j < filledFrame.cols; j++) {
            for (auto i = 0; i < filledFrame.rows; i++) {
                if (filledFrame.at<uchar>(i, j) == 255) {
                    left_border = j;
                    STOP_LOOP_FLAG = 1;
                    break;
                }
            }
            if (STOP_LOOP_FLAG) {
                STOP_LOOP_FLAG = 0;
                break;
            }
        }
        for (auto i = filledFrame.rows; i > 0; i--) {
            for (auto j = filledFrame.cols; j >0 ; j--) {
                if (filledFrame.at<uchar>(i, j) == 255) {
                    down_border = i;
                    STOP_LOOP_FLAG = 1;
                    break;
                }
            }
            if (STOP_LOOP_FLAG) {
                STOP_LOOP_FLAG = 0;
                break;
            }
        }
        for (auto j = filledFrame.cols; j > 0; j--) {
            for (auto i = 0; i < filledFrame.rows; i++) {
                if (filledFrame.at<uchar>(i, j) == 255) {
                    right_border = j;
                    STOP_LOOP_FLAG = 1;
                    break;
                }
            }
            if (STOP_LOOP_FLAG) {
                STOP_LOOP_FLAG = 0;
                break;
            }
        }
        if (left_border > right_border) {
            throw std::logic_error(
                    "Left border is greater than right border L=" + std::to_string(left_border) + ", R= " +
                    std::to_string(right_border));
        }
        if (up_border > down_border) {
            throw std::logic_error("Up border is greater than down border");
        }
        int x_cord_of_center = (left_border + right_border) / 2;
        int y_cord_of_center = (up_border + down_border) / 2;
        cv::Point center(x_cord_of_center, y_cord_of_center);
        auto test = filledFrame;
        cv::rectangle(filledFrame, cv::Point(left_border, up_border), cv::Point(right_border, down_border),
                      cv::Scalar(0, 255, 255), -1,8);
        return center;
    }


}

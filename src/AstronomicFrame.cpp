//
// Created by michal on 06.03.18.
//

#include "../include/AstronomicFrame.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


namespace Astronomic {
    std::vector<uchar> Mat2Vec(const cv::Mat img) {
        std::vector<uchar> array;
        if (img.isContinuous()) {
            array.assign(img.datastart, img.dataend);
        } else {
            for (int i = 0; i < img.rows; ++i) {
                array.insert(array.end(), img.ptr<uchar>(i), img.ptr<uchar>(i) + img.cols);
            }
        }
        return array;
    }

    cv::Mat addSlit(const cv::Mat &frame) {
        auto _frame = frame;
        for (auto i = LEFT_UP_SLIT_CORD.x; i < RIGHT_DOWN_SLIT_CORD.x; i++) {
            for (auto j = LEFT_UP_SLIT_CORD.y; j < RIGHT_DOWN_SLIT_CORD.y; j++) _frame.at<uchar>(i, j) = 255;
        }
        return _frame;
    }

    //return th= mean + C*stdev
    double calcTreshold(const std::vector<uchar> &frameData, float stdevConst) {
        float mean = (float) (std::accumulate(frameData.begin(), frameData.end(), 0.0) / frameData.size());

        double sq_sum = std::inner_product(frameData.begin(), frameData.end(), frameData.begin(), 0.0);
        double stdev = std::sqrt(sq_sum / frameData.size() - mean * mean);
        double treshold = mean + stdevConst * stdev;
        if (treshold < 1 || treshold > 60) {
            throw std::logic_error(
                    "Treshold out of the range of [0,60], was: "
                    + std::to_string(treshold));
        }
        return treshold;
    }

    AstronomicFrame AstronomicFrame::Frame2Binary() const {
        auto frameData = Mat2Vec(data);
        auto th = calcTreshold(frameData, 3);
        cv::Mat blurredAFrame;
        cv::GaussianBlur(data, blurredAFrame, cv::Size(5, 5), 3, 3, 0);
        cv::Mat binary;
        cv::threshold(data, binary, th, 255, cv::THRESH_BINARY);
        cv::medianBlur(binary, binary, 3);
        return AstronomicFrame(binary);

    }

    AstronomicFrame fillFrame(const cv::Mat frame) {
        auto tmp = addSlit(frame);
        const int KERNEL_SIZE = 5;
        auto kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE,cv::Size(KERNEL_SIZE,KERNEL_SIZE));
        cv::dilate(frame,tmp,kernel);
        return AstronomicFrame(tmp);

    }


}

//
// Created by michal on 06.03.18.
//

#include "../include/AstronomicFrame.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>




namespace AstronomicFrame {
    std::vector<uchar> Mat2Vec(const cv::Mat img) {
        std::vector<uchar> array;
        if (img.isContinuous()) {
            array.assign(img.datastart, img.dataend);
        } else {
            for (int i = 0; i < img.rows; ++i) {
                array.insert(array.end(), img.ptr<uchar>(i), img.ptr<uchar>(i)+img.cols);
            }
        }
        return array;
    }
    void addSlitMask(cv::Mat& frame){
        int y_start = Y_SLIT_CENTER_CORD - VERTICAL_SIZE/2;
        int x_start = Y_SLIT_CENTER_CORD-HORIZONTAL_SIZE/2;
        for(int i=0;i<VERTICAL_SIZE;i++){
            for(int j=0;j<HORIZONTAL_SIZE;j++){
                frame.at<uchar>(x_start+j,y_start+i) = 255;
            }
        }
    }

    //return th= mean + C*stdev
    double calcTreshold(const std::vector<uchar>& frameData, float stdevConst){
        float mean = (float)(std::accumulate(frameData.begin(),frameData.end(),0.0)/frameData.size());

        double sq_sum = std::inner_product(frameData.begin(), frameData.end(), frameData.begin(), 0.0);
        double stdev = std::sqrt(sq_sum / frameData.size() - mean * mean);
        return mean + stdevConst*stdev;
    }

    void AstronomicFrame::filtrFrame() {
        auto frameData = Mat2Vec(data);
        auto th = calcTreshold(frameData,3);
        cv::Mat blurredAFrame;
        cv::GaussianBlur(data, blurredAFrame, cv::Size(5, 5), 3, 3, 0);
        cv::Mat binary;
        cv::threshold(data,binary, th, 255, cv::THRESH_BINARY);
        cv::medianBlur(binary,binary,3);
        cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
        cv::imshow( "Display window", binary );
        cv::waitKey(0);


    }


}

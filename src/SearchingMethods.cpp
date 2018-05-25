//
// Created by michal on 14.03.18.
//

#include <opencv2/core/types.hpp>
#include <opencv2/core/mat.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "SearchingMethods.hpp"

#include <iostream>

cv::Point HoughCenter(const AstronomicFrame &frame) {
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(frame.getFrame(), circles, CV_HOUGH_GRADIENT, 1, frame.rows / 8, 200, 10, 0, 0);
    if (circles.size() != 0) return cv::Point(circles[0][0], circles[0][1]);
    else throw std::runtime_error("No Hough Circle was found");
}

cv::Point RectangleCenter(const AstronomicFrame &frame) {
    return cv::Point(frame.cols / 2, frame.rows / 2);
}

typedef std::vector<std::vector<int>> Matrix;

cv::Point HistogramCenter(const AstronomicFrame &frame) {
    Matrix matrix(frame.rows);
    for (int i = 0; i < matrix.size(); i++) matrix[i].resize(frame.cols);
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++)
            matrix[i][j] = frame.getFrame().at<int>(i, j);
    }
    std::vector<int> row_sum;
    for (auto x:matrix) row_sum.push_back(std::accumulate(x.begin(), x.end(), 0));
    std::vector<int> col_sum;
    for (int j = 0; j < frame.cols; j++) {
        int sum = 0;
        for (int i = 0; i < frame.cols; i++) sum += matrix[i][j];
        col_sum.push_back(sum);
    }
    unsigned int x_cord = std::distance(col_sum.begin(), std::max_element(col_sum.begin(), col_sum.end()));
    unsigned int y_cord;
    for(int i =0; i< col_sum.size();i++){
        int first_pos=0;
        int last_pos=col_sum.size();
        if (col_sum[i]==0) {
            first_pos=i;
            for(int j=i;j<col_sum.size();j++){
                if(col_sum[j+1]!=0) last_pos==j;
            }
            y_cord = last_pos-first_pos/2;
            break;
        }
    }
    bool isInsideFrame = x_cord < frame.cols && y_cord<frame.rows;
    if(isInsideFrame==false) throw std::runtime_error("Center using Histogram Method fail down");
    return cv::Point(x_cord, y_cord);

}
//
// Created by michal on 06.03.18.
//
#include "AstronomicFrame.hpp"
#include "SearchingMethods.hpp"
#include <iostream>


void AstronomicFrame::filtrFrame() {
    filtredFrame = frame.clone();
    cv::medianBlur(filtredFrame, filtredFrame, 3);
}

void AstronomicFrame::computeFrameToVector() {
    vectorFrame.assign(frame.datastart, frame.dataend);
    if (vectorFrame.empty())
        throw std::runtime_error("Error during converting Frame to vector");
}


AstronomicFrame AstronomicFrame::computeTrecholdedFrame(double tresholdValue) const {
    cv::Mat treshFrame;
    threshold(frame, treshFrame, tresholdValue, 255, cv::THRESH_BINARY);
    // Remove salt&pepper Noise
    cv::medianBlur(treshFrame, treshFrame, 3);
    return AstronomicFrame(treshFrame);
}

double calculateTreshold(const std::vector<int> v) {
    if (v.size() == 0) throw std::runtime_error("Can't calculate Treshold from empty vector");
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double average = (double) sum / v.size();
    double variance = 0.0;
    std::for_each(std::begin(v), std::end(v), [&](const double d) {
        variance += (d - average) * (d - average);
    });
    double stdev = sqrt((double) variance / (v.size() - 1));
    double treshold = average + 3 * stdev;//Astronomical dependence, In this case median~~average
    if (treshold > 0 & treshold < 255) return treshold;
    else throw std::runtime_error("Invalid treshold calculation");
}

AstronomicFrame FrameROI(const AstronomicFrame &frame, cv::Point &referencedCut) {
    auto binVector = frame.getvecFrame();
    int frame_cols = frame.cols;
    int frame_rows = frame.rows;
    int minrows = 0;
    int mincols = 0;
    int maxrows = frame_rows;
    int maxcols = frame_cols;
    for (int i = 0; i < binVector.size(); i++) {
        if (binVector[i] == 255) {
            if ((i / frame_cols) < maxrows)
                maxrows = (i / frame_cols);
            if (i / frame_cols > minrows)
                minrows = i / frame_cols;
            if (i % frame_cols < maxcols)
                maxcols = i % frame_cols;
            if (i % frame_cols > mincols)
                mincols = i % frame_cols;
        }
    }
    std::swap(minrows, maxrows);
    std::swap(mincols, maxcols);
    if (maxcols - mincols < 0 || maxrows - minrows < 0) throw std::logic_error("ROI not found");
    referencedCut = cv::Point(minrows, mincols);
    cv::Rect frameROI(minrows, mincols, maxcols - mincols, maxrows - minrows);
    cv::Mat roi = frame.getFrame()(frameROI);
    return AstronomicFrame(roi);
}


cv::Point calculateGuideCenter(AstronomicFrame& f, std::function<cv::Point(AstronomicFrame)> method) {
    f.filtrFrame();
    f.computeFrameToVector();
    auto grey = f.getFrame();
    auto tresh = calculateTreshold(f.getvecFrame());
    auto bin = f.computeTrecholdedFrame(tresh);
    bin.computeFrameToVector();
    cv::Point roiCorner;
    auto roi = FrameROI(bin, roiCorner);
    return roiCorner + method(f);
}
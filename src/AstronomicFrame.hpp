//
// Created by michal on 06.03.18.
//

#ifndef SLITGUIDE_ASTRONOMICFRAME_HPP
#define SLITGUIDE_ASTRONOMICFRAME_HPP
#include "Frame.hpp"

#include <opencv/cv.hpp>

class AstronomicFrame:public Frame{
private:
    cv::Mat filtredFrame;
    std::vector<int> vectorFrame;

public:
    AstronomicFrame(std::string s):Frame(s){};
    AstronomicFrame(cv::Mat m):Frame(m){};
    void filtrFrame();
    void computeFrameToVector();
    std::vector<int>  getvecFrame()const{return vectorFrame;};
    AstronomicFrame computeTrecholdedFrame(double)const;

};
double calculateTreshold(std::vector<int>);
AstronomicFrame FrameROI(const AstronomicFrame&, cv::Point&);
cv::Point calculateGuideCenter(AstronomicFrame&, std::function<cv::Point(AstronomicFrame)>);
AstronomicFrame computeBinaryFrame(AstronomicFrame& f);
#endif //SLITGUIDE_ASTRONOMICFRAME_HPP

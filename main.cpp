#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

#include "include/Frame.hpp"
#include "include/AstronomicFrame.hpp"
#include "gtest/gtest.h"
#include "CenterSearchingMethods.hpp"

using namespace Astronomic;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    for (int i = 2; i < argc; i++) {
        Astronomic::AstronomicFrame frame(std::string(argv[i]));
        auto binary_f = frame.ToBinary();
        auto filled = Astronomic::fillFrame(binary_f);
        auto tlo = cv::imread(argv[i]);
        auto x = CenterSearchingMethods::HoughCenter(filled.getFrame());
        auto y = CenterSearchingMethods::MinimumBoundignRectangleCenter(filled.getFrame());
        cv:circle(tlo, x, 3, cv::Scalar( 0, 255, 255 ),1,8,0);

        cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );// Create a window for display.
        cv::imshow( "Display window", tlo );                   // Show our image inside it.

        cv::waitKey(0);


    }


    return 0;
}

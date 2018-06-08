#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "include/SearchingMethods.hpp"

#include <iostream>

#include "include/Frame.hpp"
#include "include/AstronomicFrame.hpp"
#include "gtest/gtest.h"

using namespace AstronomicFrame;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    for (int i = 2; i < argc; i++) {
        AstronomicFrame::AstronomicFrame f(std::string(argv[i]));
        f.filtrFrame();
    }


    return 0;
}

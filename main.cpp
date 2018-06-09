#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "include/SearchingMethods.hpp"

#include <iostream>

#include "include/Frame.hpp"
#include "include/AstronomicFrame.hpp"
#include "gtest/gtest.h"

using namespace Astronomic;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    for (int i = 2; i < argc; i++) {
        Astronomic::AstronomicFrame frame(std::string(argv[i]));
        auto binary_f = frame.ToBinary();
        Astronomic::AstronomicFrame filled_frame(binary_f);
        auto x = Astronomic::fillFrame(binary_f);

    }


    return 0;
}

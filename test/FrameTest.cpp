//
// Created by michal on 13.06.18.
//

#include "FrameTest.hpp"

TEST_F(FrameTest, EmptyConstructor) {
    ASSERT_THROW(Frame f,std::invalid_argument);
}

TEST_F(FrameTest, BadPathConstructor) {
    ASSERT_THROW(Frame f(""),std::runtime_error);
}
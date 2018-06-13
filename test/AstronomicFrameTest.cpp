//
// Created by michal on 13.06.18.
//

#include "AstronomicFrameTest.hpp"

TEST_F(AstronomicFrameTest, Mat2Vec) {
    auto vec = Astronomic::Mat2Vec(Z);
    ASSERT_NE(vec.size(),0);
    EXPECT_EQ(vec[0],1);
    EXPECT_EQ(vec[5],1);
}

TEST_F(AstronomicFrameTest, calcTreshold) {
    auto th_correct = Astronomic::calcTreshold(correctVector,2);
    EXPECT_NEAR(2+2*1.0690,th_correct,0.5);
    ASSERT_THROW(Astronomic::calcTreshold(badVector,2),std::logic_error);
}
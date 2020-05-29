#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../src/util/Matrix.h"

using testing::Eq;
//
//int main(){
//    testing::InitGoogleTest();
//    return RUN_ALL_TESTS();
//}


class MatrixFixture : public ::testing::Test {
public:
    Matrix testMatrix = Matrix(2, 2);

    MatrixFixture() {
        testMatrix;
    }
};

TEST_F(MatrixFixture, firstTest) {
    ASSERT_EQ(1, 2);
}
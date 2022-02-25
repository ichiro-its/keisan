// Copyright (c) 2021 ICHIRO ITS
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <memory>

#include "gtest/gtest.h"
#include "keisan/keisan.hpp"

namespace ksn = keisan;

struct matrix_3d_inverse_args
{
  ksn::Matrix<4, 4> origin;
  ksn::Matrix<4, 4> inverse;
  bool is_invertible;
  bool is_valid;
};

class MatrixInverseTest : public ::testing::TestWithParam<matrix_3d_inverse_args>
{
protected:
  MatrixInverseTest()
  : matrix(std::make_shared<ksn::Matrix<4, 4>>(GetParam().origin))
  {
  }

  testing::AssertionResult do_test()
  {
    auto params = GetParam();

    if (matrix->inverse() != params.is_invertible) {
      return testing::AssertionFailure() << "the invertible check is failed, matrix is " <<
             (params.is_invertible ? "not" : "") << " invertible";
    }

    if (((*matrix) == params.inverse) != params.is_valid) {
      return testing::AssertionFailure() << "the result validation is failed\n" <<
             "result = " << (*matrix) << "\n" <<
             "target = " << params.inverse;
    }

    return testing::AssertionSuccess();
  }

  std::shared_ptr<ksn::Matrix<4, 4>> matrix;
};

TEST_P(MatrixInverseTest, Inverse)
{
  EXPECT_TRUE(do_test());
}

matrix_3d_inverse_args test_case_1 = {
  ksn::Matrix<4, 4>(
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0),
  ksn::Matrix<4, 4>(
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0),
  true,
  true
};

matrix_3d_inverse_args test_case_2 = {
  ksn::Matrix<4, 4>(
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 1.0, 0.0,
    0.0, 1.0, 1.0, 0.0,
    1.0, 0.0, 0.0, 1.0),
  ksn::Matrix<4, 4>::zero(),
  false,
  false
};

matrix_3d_inverse_args test_case_3 = {
  ksn::Matrix<4, 4>(
    1.0, 1.0, 1.0, 1.0,
    1.0, 5.0, 3.0, 0.0,
    1.0, 1.0, 6.0, 1.0,
    1.0, 1.0, 1.0, 0.0),
  ksn::Matrix<4, 4>(
    1.0 / 10.0, -1.0 / 4.0, -1.0 / 10.0, 5.0 / 4.0,
    1.0 / 10.0, 1.0 / 4.0, -1.0 / 10.0, -1.0 / 4.0,
    -1.0 / 5.0, 0.0, 1.0 / 5.0, 0.0,
    1.0, 0.0, 0.0, -1.0),
  true,
  true
};

matrix_3d_inverse_args test_case_4 = {
  ksn::Matrix<4, 4>(
    1.0, 1.0, 1.0, 1.0,
    1.0, 0.0, 3.0, 0.0,
    0.0, 1.0, 6.0, 1.0,
    8.0, 1.0, 1.0, 0.0),
  ksn::Matrix<4, 4>(
    3.0 / 8.0, 5.0 / 8.0, -3.0 / 8.0, 0.0,
    -23.0 / 8.0, -41.0 / 8.0, 23.0 / 8.0, 1.0,
    -1.0 / 8.0, 1.0 / 8.0, 1.0 / 8.0, 0.0,
    29.0 / 8.0, 35.0 / 8.0, -21.0 / 8.0, -1.0),
  true,
  true
};

matrix_3d_inverse_args test_case_5 = {
  ksn::Matrix<4, 4>(
    1.0, 1.0, 1.0, 1.0,
    1.0, 0.0, 3.0, 0.0,
    0.0, 1.0, 6.0, 1.0,
    8.0, 1.0, 1.0, 0.0),
  ksn::Matrix<4, 4>(
    3.0 / 8.0, 5.0 / 8.0, -3.0 / 8.0, 0.0,
    -23.0 / 8.0, -41.0 / 8.0, 23.0 / 8.0, 1.0,
    -1.0 / 8.0, 1.0 / 8.0, 1.0 / 8.0, 0.0,
    29.0 / 8.0, 35.0 / 8.0, -21.0 / 8.0, 0.0),
  true,
  false
};

matrix_3d_inverse_args test_case_6 = {
  ksn::Matrix<4, 4>(
    1.0, 1.0, 2.0, 1.0,
    1.0, 0.0, 3.0, 0.0,
    0.0, 1.0, 6.0, 1.0,
    8.0, 1.0, 3.0, 0.0),
  ksn::Matrix<4, 4>(
    3.0 / 7.0, 4.0 / 7.0, -3.0 / 7.0, 0.0,
    -21.0 / 7.0, -35.0 / 7.0, 21.0 / 7.0, 1.0,
    -1.0 / 7.0, 1.0 / 7.0, 1.0 / 7.0, 0.0,
    27.0 / 7.0, 29.0 / 7.0, -20.0 / 7.0, -1.0),
  true,
  true
};

INSTANTIATE_TEST_CASE_P(
  InverseTest,
  MatrixInverseTest,
  testing::Values(
    test_case_1, test_case_2, test_case_3,
    test_case_4, test_case_5, test_case_6));

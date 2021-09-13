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

#ifndef COMPARISON__POINT_2_HPP_
#define COMPARISON__POINT_2_HPP_

#include <limits>
#include <string>

#include "keisan/keisan.hpp"

#include "./almost_equal.hpp"

namespace testing
{

std::string point2_print_string(const keisan::Point2 & point)
{
  std::stringstream ss;
  ss << std::setprecision(std::numeric_limits<double>::digits10 + 2) <<
    "{" << point.x << ", " << point.y << "}";

  return internal::StringStreamToString(&ss);
}

AssertionResult point2_equal(
  const char * lhs_expression, const char * rhs_expression,
  const keisan::Point2 & lhs_value, const keisan::Point2 & rhs_value)
{
  if (almost_equal(lhs_value.x, rhs_value.x) && almost_equal(lhs_value.y, rhs_value.y)) {
    return AssertionSuccess();
  }

  return internal::EqFailure(
    lhs_expression, rhs_expression,
    point2_print_string(lhs_value), point2_print_string(rhs_value),
    false);
}

#define EXPECT_POINT2_EQ(val1, val2) \
  EXPECT_PRED_FORMAT2(testing::point2_equal, val1, val2)

#define ASSERT_POINT2_EQ(val1, val2) \
  ASSERT_PRED_FORMAT2(testing::point2_equal, val1, val2)

}  // namespace testing

#endif  // COMPARISON__POINT_2_HPP_

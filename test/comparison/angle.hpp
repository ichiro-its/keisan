// Copyright (c) 2022 ICHIRO ITS
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

#ifndef COMPARISON__ANGLE_HPP_
#define COMPARISON__ANGLE_HPP_

#include <limits>
#include <string>

#include "keisan/keisan.hpp"

#include "almost_equal.hpp"

namespace testing
{

std::string deg_angle_print_string(const keisan::DegAngle<float> & angle)
{
  std::stringstream ss;
  ss << std::setprecision(std::numeric_limits<float>::digits10 + 2) <<
    angle.degree() << "_deg";

  return internal::StringStreamToString(&ss);
}

AssertionResult deg_angle_equal(
  const char * lhs_expression, const char * rhs_expression,
  const keisan::DegAngle<float> & lhs_value, const keisan::DegAngle<float> & rhs_value)
{
  if (almost_equal(lhs_value.degree(), rhs_value.degree())) {
    return AssertionSuccess();
  }

  return internal::EqFailure(
    lhs_expression, rhs_expression,
    deg_angle_print_string(lhs_value), deg_angle_print_string(rhs_value),
    false);
}

#define EXPECT_ANGLE_EQ(VAL1, VAL2) \
  EXPECT_PRED_FORMAT2(testing::deg_angle_equal, VAL1, VAL2)

#define ASSERT_ANGLE_EQ(VAL1, VAL2) \
  ASSERT_PRED_FORMAT2(testing::deg_angle_equal, VAL1, VAL2)

}  // namespace testing

#endif  // COMPARISON__ANGLE_HPP_

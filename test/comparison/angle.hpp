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

#ifndef COMPARISON__ANGLE_HPP_
#define COMPARISON__ANGLE_HPP_

#include <limits>
#include <string>

#include "keisan/keisan.hpp"

#include "./almost_equal.hpp"

namespace testing
{

template<typename T>
std::string to_string(const keisan::Angle<T> & angle)
{
  std::stringstream ss;
  ss << angle.degree();
  return internal::StringStreamToString(&ss);
}

template<typename T>
AssertionResult angle_equal(
  const char * lhs_exp, const char * rhs_exp,
  const keisan::Angle<T> & lhs, const keisan::Angle<T> & rhs)
{
  if constexpr (std::is_floating_point<T>::value) {
    if (almost_equal(lhs.radian(), rhs.radian()) || almost_equal(lhs.degree(), rhs.degree())) {
      return AssertionSuccess();
    }
  } else {
    if (lhs == rhs) {
      return AssertionSuccess();
    }
  }

  return internal::EqFailure(lhs_exp, rhs_exp, to_string(lhs), to_string(rhs), false);
}

#define EXPECT_ANGLE_EQ(lhs, rhs) \
  EXPECT_PRED_FORMAT2(testing::angle_equal, lhs, rhs)

#define ASSERT_ANGLE_EQ(lhs, rhs) \
  ASSERT_PRED_FORMAT2(testing::angle_equal, lhs, rhs)

}  // namespace testing

#endif  // COMPARISON__ANGLE_HPP_

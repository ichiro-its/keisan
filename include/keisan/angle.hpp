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

#ifndef KEISAN__ANGLE_HPP_
#define KEISAN__ANGLE_HPP_

#include <keisan/number.hpp>
#include <cmath>

namespace keisan
{
constexpr double pi = atan(1.0) * 4;

template<typename T>
T wrap_rad(T value)
{
  return wrap_number<T>(value, -pi, pi);
}

template<typename T>
T wrap_deg(T value)
{
  return wrap_number(value, -180.0, 180.0);
}

template<typename T>
T rad_to_deg(T value)
{
  return wrap_deg(scale_number(value, pi, 180.0));
}

template<typename T>
T deg_to_rad(T value)
{
  return wrap_rad(scale_number(value, 180.0, pi));
}

template<typename M, typename N>
M delta_rad(M value1, N value2)
{
  return wrap_rad(wrap_rad(value2) - wrap_rad(value1));
}

template<typename M, typename N>
M delta_deg(M value1, N value2)
{
  return wrap_deg(wrap_deg(value2) - wrap_deg(value1));
}

}  // namespace keisan

#endif  // KEISAN__ANGLE_HPP_

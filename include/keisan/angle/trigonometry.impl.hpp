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

#ifndef KEISAN__ANGLE__TRIGONOMETRY_IMPL_HPP_
#define KEISAN__ANGLE__TRIGONOMETRY_IMPL_HPP_

#include "keisan/angle/angle.hpp"
#include "keisan/angle/trigonometry.hpp"

namespace keisan
{

template<typename T>
T sin(const Angle<T> & angle)
{
  return std::sin(angle.radian());
}

template<typename T>
T cos(const Angle<T> & angle)
{
  return std::cos(angle.radian());
}

template<typename T>
T tan(const Angle<T> & angle)
{
  return std::tan(angle.radian());
}

template<typename T>
Angle<T> arcsin(const T & value)
{
  return make_radian(std::asin(value));
}

template<typename T>
Angle<T> arccos(const T & value)
{
  return make_radian(std::acos(value));
}

template<typename T>
Angle<T> arctan(const T & value)
{
  return make_radian(std::atan(value));
}

template<typename T>
Angle<T> signed_arctan(const T & y, const T & x)
{
  return make_radian(std::atan2(y, x));
}

}  // namespace keisan

#endif  // KEISAN__ANGLE__TRIGONOMETRY_IMPL_HPP_
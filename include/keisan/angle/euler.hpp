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

#ifndef KEISAN__ANGLE__EULER_HPP_
#define KEISAN__ANGLE__EULER_HPP_

#include <iostream>

#include "keisan/angle/angle_type.hpp"
#include "keisan/angle/angle.hpp"

namespace keisan
{

// Forward declaration
template<typename T>
struct Quaternion;

template<AngleType E, typename T>
struct Euler
{
  Euler();
  Euler(const Angle<E, T> & roll, const Angle<E, T> & pitch, const Angle<E, T> & yaw);

  template<typename U>
  operator Euler<E, U>() const;

  bool operator==(const Euler<E, T> & other) const;
  bool operator!=(const Euler<E, T> & other) const;

  Quaternion<T> to_quaternion() const;

  Angle<E, T> roll;
  Angle<E, T> pitch;
  Angle<E, T> yaw;
};

template<typename T>
using DegEuler = Euler<AngleType::Degree, T>;

template<typename T>
using RadEuler = Euler<AngleType::Radian, T>;

}  // namespace keisan

template<keisan::AngleType E, typename T>
std::ostream & operator<<(std::ostream & out, const keisan::Euler<E, T> & euler);

#include "keisan/angle/euler.impl.hpp"

#endif  // KEISAN__ANGLE__EULER_HPP_

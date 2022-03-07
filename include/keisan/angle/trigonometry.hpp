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

#ifndef KEISAN__ANGLE__TRIGONOMETRY_HPP_
#define KEISAN__ANGLE__TRIGONOMETRY_HPP_

#include <cmath>

#include "keisan/angle/angle_type.hpp"

namespace keisan
{

// Forward declaration
template<AngleType E, typename T>
class Angle;

template<typename T>
const T pi = std::atan((T)1) * 4;

template<AngleType E, typename T>
T sin(const Angle<E, T> & angle);

template<AngleType E, typename T>
T cos(const Angle<E, T> & angle);

template<AngleType E, typename T>
T tan(const Angle<E, T> & angle);

template<typename T>
Angle<AngleType::Radian, T> arcsin(const T & value);

template<typename T>
Angle<AngleType::Radian, T> arccos(const T & value);

template<typename T>
Angle<AngleType::Radian, T> arctan(const T & value);

template<typename T>
Angle<AngleType::Radian, T> signed_arctan(const T & y, const T & x);

namespace literals
{

double operator""_pi(unsigned long long int value);  // NOLINT
double operator""_pi(long double value);

}  // namespace literals

}  // namespace keisan

#include "keisan/angle/trigonometry.impl.hpp"

#endif  // KEISAN__ANGLE__TRIGONOMETRY_HPP_

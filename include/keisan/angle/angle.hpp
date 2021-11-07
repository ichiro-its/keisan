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

#ifndef KEISAN__ANGLE__ANGLE_HPP_
#define KEISAN__ANGLE__ANGLE_HPP_

#include <iostream>

#include "keisan/angle/angle_type.hpp"

namespace keisan
{

template<AngleType E, typename T>
struct Angle
{
  T value;

  // template<typename U>
  // friend class Angle;

  Angle();
  explicit Angle(const T & value);

  // template<typename U>
  // operator Angle<U>() const;

  bool operator==(const Angle<E, T> & other) const;
  bool operator!=(const Angle<E, T> & other) const;
  bool operator>(const Angle<E, T> & other) const;
  bool operator>=(const Angle<E, T> & other) const;
  bool operator<(const Angle<E, T> & other) const;
  bool operator<=(const Angle<E, T> & other) const;

  Angle<E, T> & operator+=(const Angle<E, T> & other);
  Angle<E, T> & operator-=(const Angle<E, T> & other);

  Angle<E, T> & operator*=(const T & value);
  Angle<E, T> & operator/=(const T & value);

  Angle<E, T> operator+(const Angle<E, T> & other) const;
  Angle<E, T> operator-(const Angle<E, T> & other) const;

  Angle<E, T> operator*(const T & value) const;
  Angle<E, T> operator/(const T & value) const;

  Angle<E, T> operator-() const;

  Angle<E, T> normalize() const;
};

template<typename T>
using DegAngle = Angle<AngleType::Degree, T>;

template<typename T>
using RadAngle = Angle<AngleType::Radian, T>;

namespace literals
{

DegAngle<long long int> operator""_deg(unsigned long long int value);  // NOLINT
DegAngle<long double> operator""_deg(long double value);

RadAngle<long double> operator""_pi_rad(unsigned long long int value);  // NOLINT
RadAngle<long double> operator""_pi_rad(long double value);

}  // namespace literals

}  // namespace keisan

template<keisan::AngleType E, typename T>
std::ostream & operator<<(std::ostream & out, const keisan::Angle<E, T> & angle);

template<keisan::AngleType E, typename T, typename U>
keisan::Angle<E, T> operator*(const U & value, const keisan::Angle<E, T> & angle);

#include "keisan/angle/angle.impl.hpp"

#endif  // KEISAN__ANGLE__ANGLE_HPP_

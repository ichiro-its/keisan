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

#include "keisan/angle/angle_type.hpp"

namespace keisan
{

template<AngleType E, typename T>
struct Angle;

template<typename T>
using DegAngle = Angle<AngleType::Degree, T>;

template<typename T>
using RadAngle = Angle<AngleType::Radian, T>;

template<AngleType E, typename T>
class Angle
{
private:
  T value;

public:
  Angle();
  explicit Angle(const T & value);

  template<AngleType F, typename U>
  operator Angle<F, U>() const;

  template<AngleType F, typename U>
  bool operator==(const Angle<F, U> & other) const;

  template<AngleType F, typename U>
  bool operator!=(const Angle<F, U> & other) const;

  template<AngleType F, typename U>
  bool operator>(const Angle<F, U> & other) const;

  template<AngleType F, typename U>
  bool operator>=(const Angle<F, U> & other) const;

  template<AngleType F, typename U>
  bool operator<(const Angle<F, U> & other) const;

  template<AngleType F, typename U>
  bool operator<=(const Angle<F, U> & other) const;

  template<AngleType F, typename U>
  Angle<E, T> & operator+=(const Angle<F, U> & other);

  template<AngleType F, typename U>
  Angle<E, T> & operator-=(const Angle<F, U> & other);

  template<typename U>
  Angle<E, T> & operator*=(U value);

  template<typename U>
  Angle<E, T> & operator/=(U value);

  template<AngleType F, typename U>
  Angle<E, T> operator+(const Angle<F, U> & other) const;

  template<AngleType F, typename U>
  Angle<E, T> operator-(const Angle<F, U> & other) const;

  template<typename U>
  Angle<E, T> operator*(U value) const;

  template<typename U>
  Angle<E, T> operator/(U value) const;

  Angle<E, T> operator-() const;

  DegAngle<T> to_deg_angle() const;
  RadAngle<T> to_rad_angle() const;

  template<AngleType F>
  T value_in() const;

  T degree() const;
  T radian() const;

  Angle<E, T> normalize() const;
};

namespace angle
{
template<typename T>
DegAngle<T> from_degree(T value);

template<typename T>
RadAngle<T> from_radian(T value);
}  // namespace angle

template<typename T>
[[deprecated("use keisan::angle::from_degree instead")]]
DegAngle<T> make_degree(T value);

template<typename T>
[[deprecated("use keisan::angle::from_radian instead")]]
RadAngle<T> make_radian(T value);

namespace literals
{
DegAngle<long long int> operator""_deg(unsigned long long int value);  // NOLINT
DegAngle<long double> operator""_deg(long double value);

RadAngle<long double> operator""_pi_rad(unsigned long long int value);  // NOLINT
RadAngle<long double> operator""_pi_rad(long double value);
}  // namespace literals

}  // namespace keisan

template<keisan::AngleType E, typename T, typename U>
keisan::Angle<E, T> operator*(const U & value, const keisan::Angle<E, T> & angle);

#include "keisan/angle/angle.impl.hpp"

#endif  // KEISAN__ANGLE__ANGLE_HPP_

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

#ifndef KEISAN__ANGLE__ANGLE_IMPL_HPP_
#define KEISAN__ANGLE__ANGLE_IMPL_HPP_

#include "keisan/number.hpp"
#include "keisan/angle/trigonometry.hpp"

template<keisan::AngleType E, typename T>
std::ostream & operator<<(std::ostream & out, const keisan::Angle<E, T> & angle)
{
  switch (E) {
    case keisan::AngleType::Degree: return out << angle.degree() << "_deg";
    case keisan::AngleType::Radian: return out << angle.radian() << "_pi_rad";
  }
}

template<keisan::AngleType E, typename T, typename U>
keisan::Angle<E, T> operator*(const U & value, const keisan::Angle<E, T> & angle)
{
  return angle * value;
}

namespace keisan
{

namespace angle
{

template<typename T>
DegAngle<T> from_degree(T value)
{
  return DegAngle<T>(value);
}

template<typename T>
RadAngle<T> from_radian(T value)
{
  return RadAngle<T>(value);
}

}  // namespace angle

template<typename T>
DegAngle<T> make_degree(T value)
{
  return angle::from_degree(value);
}

template<typename T>
RadAngle<T> make_radian(T value)
{
  return angle::from_radian(value);
}

template<AngleType E, typename T>
Angle<E, T>::Angle()
{
}

template<AngleType E, typename T>
Angle<E, T>::Angle(const T & value)
: value(value)
{
}

template<AngleType E, typename T>
template<AngleType F, typename U>
Angle<E, T>::operator Angle<F, U>() const
{
  if (E == F) {
    return Angle<F, U>(value);
  } else {
    switch (F) {
      case AngleType::Degree: return to_deg_angle();
      case AngleType::Radian: return to_rad_angle();
    }
  }
}

template<AngleType E, typename T>
template<AngleType F, typename U>
bool Angle<E, T>::operator==(const Angle<F, U> & other) const
{
  return value == other.template value_in<F>();
}

template<AngleType E, typename T>
template<AngleType F, typename U>
bool Angle<E, T>::operator!=(const Angle<F, U> & other) const
{
  return value != other.template value_in<F>();
}

template<AngleType E, typename T>
template<AngleType F, typename U>
bool Angle<E, T>::operator>(const Angle<F, U> & other) const
{
  return value > other.template value_in<F>();
}

template<AngleType E, typename T>
template<AngleType F, typename U>
bool Angle<E, T>::operator>=(const Angle<F, U> & other) const
{
  return value >= other.template value_in<F>();
}

template<AngleType E, typename T>
template<AngleType F, typename U>
bool Angle<E, T>::operator<(const Angle<F, U> & other) const
{
  return value < other.template value_in<F>();
}

template<AngleType E, typename T>
template<AngleType F, typename U>
bool Angle<E, T>::operator<=(const Angle<F, U> & other) const
{
  return value <= other.template value_in<F>();
}

template<AngleType E, typename T>
template<AngleType F, typename U>
Angle<E, T> & Angle<E, T>::operator+=(const Angle<F, U> & other)
{
  value += other.template value_in<F>();
  return *this;
}

template<AngleType E, typename T>
template<AngleType F, typename U>
Angle<E, T> & Angle<E, T>::operator-=(const Angle<F, U> & other)
{
  value -= other.template value_in<F>();
  return *this;
}

template<AngleType E, typename T>
template<typename U>
Angle<E, T> & Angle<E, T>::operator*=(U value)
{
  this->value *= value;
  return *this;
}

template<AngleType E, typename T>
template<typename U>
Angle<E, T> & Angle<E, T>::operator/=(U value)
{
  this->value /= value;
  return *this;
}

template<AngleType E, typename T>
template<AngleType F, typename U>
Angle<E, T> Angle<E, T>::operator+(const Angle<F, U> & other) const
{
  return Angle<E, T>(value + other.template value_in<F>());
}

template<AngleType E, typename T>
template<AngleType F, typename U>
Angle<E, T> Angle<E, T>::operator-(const Angle<F, U> & other) const
{
  return Angle<E, T>(value - other.template value_in<F>());
}

template<AngleType E, typename T>
template<typename U>
Angle<E, T> Angle<E, T>::operator*(U value) const
{
  return Angle<E, T>(this->value * value);
}

template<AngleType E, typename T>
template<typename U>
Angle<E, T> Angle<E, T>::operator/(U value) const
{
  return Angle<E, T>(this->value / value);
}

template<AngleType E, typename T>
Angle<E, T> Angle<E, T>::operator-() const
{
  return Angle<E, T>(-value);
}

template<AngleType E, typename T>
DegAngle<T> Angle<E, T>::to_deg_angle() const
{
  if (E == AngleType::Degree) {
    return *this;
  } else {
    return DegAngle<T>(degree());
  }
}

template<AngleType E, typename T>
RadAngle<T> Angle<E, T>::to_rad_angle() const
{
  if (E == AngleType::Radian) {
    return *this;
  } else {
    return RadAngle<T>(radian());
  }
}

template<AngleType E, typename T>
template<AngleType F>
T Angle<E, T>::value_in() const
{
  if (E == F) {
    return value;
  } else {
    using keisan::literals::operator""_pi;
    switch (F) {
      case AngleType::Degree: return scale<T>(value, 1_pi, 180);
      case AngleType::Radian: return scale<T>(value, 180, 1_pi);
    }
  }
}

template<AngleType E, typename T>
T Angle<E, T>::degree() const
{
  return value_in<AngleType::Degree>();
}

template<AngleType E, typename T>
T Angle<E, T>::radian() const
{
  return value_in<AngleType::Radian>();
}

template<AngleType E, typename T>
Angle<E, T> Angle<E, T>::normalize() const
{
  using keisan::literals::operator""_pi;
  switch (E) {
    case AngleType::Degree: return angle::from_degree(wrap<T>(value, -180, 180));
    case AngleType::Radian: return angle::from_radian(wrap<T>(value, -1_pi, 1_pi));
  }
}

}  // namespace keisan

#endif  // KEISAN__ANGLE__ANGLE_IMPL_HPP_

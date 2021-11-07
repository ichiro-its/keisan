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
#include "keisan/angle/angle.hpp"
#include "keisan/angle/trigonometry.hpp"

template<keisan::AngleType E, typename T>
std::ostream & operator<<(std::ostream & out, const keisan::Angle<E, T> & angle)
{
  return out << angle.value;
}

template<keisan::AngleType E, typename T, typename U>
keisan::Angle<E, T> operator*(const U & value, const keisan::Angle<E, T> & angle)
{
  return angle * value;
}

namespace keisan
{

template<AngleType E, typename T>
Angle<E, T>::Angle()
{
}

template<AngleType E, typename T>
Angle<E, T>::Angle(const T & value)
: value(value)
{
}

// template<typename T>
// template<typename U>
// Angle<T>::operator Angle<U>() const
// {
//   return Angle<U>(data, is_degree);
// }

template<AngleType E, typename T>
bool Angle<E, T>::operator==(const Angle<E, T> & other) const
{
  return value == other.value;
}

template<AngleType E, typename T>
bool Angle<E, T>::operator!=(const Angle<E, T> & other) const
{
  return value != other.value;
}

template<AngleType E, typename T>
bool Angle<E, T>::operator>(const Angle<E, T> & other) const
{
  return value > other.value;
}

template<AngleType E, typename T>
bool Angle<E, T>::operator>=(const Angle<E, T> & other) const
{
  return value >= other.value;
}

template<AngleType E, typename T>
bool Angle<E, T>::operator<(const Angle<E, T> & other) const
{
  return value < other.value;
}

template<AngleType E, typename T>
bool Angle<E, T>::operator<=(const Angle<E, T> & other) const
{
  return value <= other.value;
}

template<AngleType E, typename T>
Angle<E, T> & Angle<E, T>::operator+=(const Angle<E, T> & other)
{
  value += other.value;
  return *this;
}

template<AngleType E, typename T>
Angle<E, T> & Angle<E, T>::operator-=(const Angle<E, T> & other)
{
  value -= other.value;
  return *this;
}

template<AngleType E, typename T>
Angle<E, T> & Angle<E, T>::operator*=(const T & value)
{
  this->value *= value;
  return *this;
}

template<AngleType E, typename T>
Angle<E, T> & Angle<E, T>::operator/=(const T & value)
{
  this->value /= value;
  return *this;
}

template<AngleType E, typename T>
Angle<E, T> Angle<E, T>::operator+(const Angle<E, T> & other) const
{
  return Angle<E, T>(value + other.value);
}

template<AngleType E, typename T>
Angle<E, T> Angle<E, T>::operator-(const Angle<E, T> & other) const
{
  return Angle<E, T>(value - other.value);
}

template<AngleType E, typename T>
Angle<E, T> Angle<E, T>::operator*(const T & value) const
{
  return Angle<E, T>(this->value * value);
}

template<AngleType E, typename T>
Angle<E, T> Angle<E, T>::operator/(const T & value) const
{
  return Angle<E, T>(this->value / value);
}

template<AngleType E, typename T>
Angle<E, T> Angle<E, T>::operator-() const
{
  return Angle<E, T>(-value);
}

// template<typename T>
// T Angle<T>::degree() const
// {
//   using keisan::literals::operator""_pi;

//   return is_degree ? data : scale<T>(data, 1_pi, 180.0);
// }

// template<typename T>
// T Angle<T>::radian() const
// {
//   using keisan::literals::operator""_pi;

//   return is_degree ? scale<T>(data, 180.0, 1_pi) : data;
// }

template<typename T>
DegAngle<T> Angle<AngleType::Degree, T>::normalize() const
{
  return Degree(wrap<T>(value, -180, 180));
}

template<typename T>
RadAngle<T> Angle<AngleType::Radian, T>::normalize() const
{
  using keisan::literals::operator""_pi;
  return Radian(wrap<T>(value, -1_pi, 1_pi));
}

}  // namespace keisan

#endif  // KEISAN__ANGLE__ANGLE_IMPL_HPP_

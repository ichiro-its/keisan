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

template<typename T>
std::ostream & operator<<(std::ostream & out, const keisan::Angle<T> & angle)
{
  return out << angle.degree();
}

namespace keisan
{

template<typename T>
Angle<T> make_degree(const T & value)
{
  return Angle<T>(value, true);
}

template<typename T>
Angle<T> make_radian(const T & value)
{
  return Angle<T>(value, false);
}

template<typename T, typename U>
Angle<T> operator*(const U & value, const Angle<T> & angle)
{
  return angle * value;
}

template<typename T>
Angle<T> difference_between(const Angle<T> & a, const Angle<T> & b)
{
  return a.difference_to(b);
}

template<typename T>
Angle<T>::Angle()
{
}

template<typename T>
Angle<T>::Angle(const T & data, const bool & is_degree)
: data(data),
  is_degree(is_degree)
{
}

template<typename T>
template<typename U>
Angle<T>::operator Angle<U>() const
{
  return Angle<U>(data, is_degree);
}

template<typename T>
bool Angle<T>::operator==(const Angle<T> & angle) const
{
  return data == (is_degree ? angle.degree() : angle.radian());
}

template<typename T>
bool Angle<T>::operator!=(const Angle<T> & angle) const
{
  return data != (is_degree ? angle.degree() : angle.radian());
}

template<typename T>
bool Angle<T>::operator>(const Angle<T> & angle) const
{
  return data > (is_degree ? angle.degree() : angle.radian());
}

template<typename T>
bool Angle<T>::operator>=(const Angle<T> & angle) const
{
  return data >= (is_degree ? angle.degree() : angle.radian());
}

template<typename T>
bool Angle<T>::operator<(const Angle<T> & angle) const
{
  return data < (is_degree ? angle.degree() : angle.radian());
}

template<typename T>
bool Angle<T>::operator<=(const Angle<T> & angle) const
{
  return data <= (is_degree ? angle.degree() : angle.radian());
}

template<typename T>
Angle<T> & Angle<T>::operator+=(const Angle<T> & angle)
{
  data += is_degree ? angle.degree() : angle.radian();
  return *this;
}

template<typename T>
Angle<T> & Angle<T>::operator-=(const Angle<T> & angle)
{
  data -= is_degree ? angle.degree() : angle.radian();
  return *this;
}

template<typename T>
Angle<T> & Angle<T>::operator*=(const T & value)
{
  data *= value;
  return *this;
}

template<typename T>
Angle<T> & Angle<T>::operator/=(const T & value)
{
  data /= value;
  return *this;
}

template<typename T>
Angle<T> Angle<T>::operator+(const Angle<T> & angle) const
{
  return Angle(data + (is_degree ? angle.degree() : angle.radian()), is_degree);
}

template<typename T>
Angle<T> Angle<T>::operator-(const Angle<T> & angle) const
{
  return Angle(data - (is_degree ? angle.degree() : angle.radian()), is_degree);
}

template<typename T>
Angle<T> Angle<T>::operator*(const T & value) const
{
  return Angle(data * value, is_degree);
}

template<typename T>
Angle<T> Angle<T>::operator/(const T & value) const
{
  return Angle(data / value, is_degree);
}

template<typename T>
Angle<T> Angle<T>::operator-() const
{
  return Angle(-data, is_degree);
}

template<typename T>
T Angle<T>::degree() const
{
  using keisan::literals::operator""_pi;

  return is_degree ? data : scale<T>(data, 1_pi, 180.0);
}

template<typename T>
T Angle<T>::radian() const
{
  using keisan::literals::operator""_pi;

  return is_degree ? scale<T>(data, 180.0, 1_pi) : data;
}

template<typename T>
Angle<T> Angle<T>::normalize() const
{
  using keisan::literals::operator""_pi;

  if (is_degree) {
    return make_degree(wrap<T>(data, -180.0, 180.0));
  } else {
    return make_radian(wrap<T>(data, -1_pi, 1_pi));
  }
}

template<typename T>
Angle<T> Angle<T>::difference_to(const Angle<T> & angle) const
{
  return (angle - *this).normalize();
}

}  // namespace keisan

#endif  // KEISAN__ANGLE__ANGLE_IMPL_HPP_

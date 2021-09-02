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

namespace keisan
{

// Forward declaration
template<typename T>
class Angle;

template<typename T>
Angle<T> make_degree(const T & value);

template<typename T>
Angle<T> make_radian(const T & value);

template<typename T>
class Angle
{
public:
  template<typename U>
  friend class Angle;

  friend Angle<T> make_degree<T>(const T & value);
  friend Angle<T> make_radian<T>(const T & value);

  Angle();

private:
  explicit Angle(const T & data, const bool & is_degree = false);

public:
  template<typename U>
  operator Angle<U>() const;

  bool operator==(const Angle<T> & angle) const;
  bool operator!=(const Angle<T> & angle) const;
  bool operator>(const Angle<T> & angle) const;
  bool operator>=(const Angle<T> & angle) const;
  bool operator<(const Angle<T> & angle) const;
  bool operator<=(const Angle<T> & angle) const;

  Angle<T> & operator+=(const Angle<T> & angle);
  Angle<T> & operator-=(const Angle<T> & angle);

  Angle<T> & operator*=(const T & value);
  Angle<T> & operator/=(const T & value);

  Angle<T> operator+(const Angle<T> & angle) const;
  Angle<T> operator-(const Angle<T> & angle) const;

  Angle<T> operator*(const T & value) const;
  Angle<T> operator/(const T & value) const;

  Angle<T> operator-() const;

  T degree() const;
  T radian() const;

  Angle<T> normalize() const;

  Angle<T> difference_to(const Angle<T> & angle) const;

private:
  T data;
  bool is_degree;
};

template<typename T, typename U>
Angle<T> operator*(const U & value, const Angle<T> & angle);

template<typename T>
Angle<T> difference_between(const Angle<T> & a, const Angle<T> & b);

namespace literals
{

Angle<double> operator""_deg(unsigned long long int value);  // NOLINT
Angle<double> operator""_deg(long double value);

Angle<double> operator""_pi_rad(unsigned long long int value);  // NOLINT
Angle<double> operator""_pi_rad(long double value);

}  // namespace literals

}  // namespace keisan

template<typename T>
std::ostream & operator<<(std::ostream & out, const keisan::Angle<T> & angle);

#include "keisan/angle/angle.impl.hpp"

#endif  // KEISAN__ANGLE__ANGLE_HPP_

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

#include <cmath>

namespace keisan
{

constexpr double pi = std::atan(1.0) * 4;

class Angle;

Angle make_degree(const double & value);
Angle make_radian(const double & value);

Angle difference_between(const Angle & a, const Angle & b);

class Angle
{
public:
  Angle();
  explicit Angle(const double & data, const bool & is_degree = false);

  Angle(const Angle & angle);

  Angle & operator=(const Angle & angle);

  bool operator==(const Angle & angle) const;
  bool operator>(const Angle & angle) const;
  bool operator>=(const Angle & angle) const;
  bool operator<(const Angle & angle) const;
  bool operator<=(const Angle & angle) const;

  Angle & operator+=(const Angle & angle);
  Angle & operator-=(const Angle & angle);

  Angle & operator*=(const double & value);
  Angle & operator/=(const double & value);

  Angle operator+(const Angle & angle) const;
  Angle operator-(const Angle & angle) const;

  Angle operator*(const double & value) const;
  Angle operator/(const double & value) const;

  Angle operator-() const;

  double degree() const;
  double radian() const;

  Angle normalize() const;

  Angle difference_to(const Angle & angle) const;

private:
  double data;
  bool is_degree;
};

}  // namespace keisan

#endif  // KEISAN__ANGLE__ANGLE_HPP_

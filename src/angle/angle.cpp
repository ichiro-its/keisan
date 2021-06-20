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

#include <keisan/angle/angle.hpp>
#include <keisan/number.hpp>

namespace keisan
{
constexpr double pi = 3.14159265359;

Angle make_degree(const double & value)
{
  return Angle(value, true);
}

Angle make_radian(const double & value)
{
  return Angle(value, false);
}

Angle::Angle(const double & data, const bool & is_degree)
: data(data),
  is_degree(is_degree)
{
}

Angle::Angle(const Angle & angle)
{
  *this = angle;
}

Angle & Angle::operator=(const Angle & angle)
{
  data = angle.data;
  is_degree = angle.is_degree;

  return *this;
}

Angle & Angle::operator+=(const Angle & angle)
{
  data += is_degree ? angle.degree() : angle.radian();
  return *this;
}

Angle & Angle::operator-=(const Angle & angle)
{
  data -= is_degree ? angle.degree() : angle.radian();
  return *this;
}

Angle & Angle::operator+=(const double & value)
{
  data += value;
  return *this;
}

Angle & Angle::operator-=(const double & value)
{
  data -= value;
  return *this;
}

Angle & Angle::operator*=(const double & value)
{
  data *= value;
  return *this;
}

Angle & Angle::operator/=(const double & value)
{
  data /= value;
  return *this;
}

Angle Angle::operator+(const Angle & angle)
{
  return Angle(data + is_degree ? angle.degree() : angle.radian(), is_degree);
}

Angle Angle::operator-(const Angle & angle)
{
  return Angle(data - is_degree ? angle.degree() : angle.radian(), is_degree);
}

Angle Angle::operator+(const double & value)
{
  return Angle(data + value, is_degree);
}

Angle Angle::operator-(const double & value)
{
  return Angle(data - value, is_degree);
}

Angle Angle::operator*(const double & value)
{
  return Angle(data * value, is_degree);
}

Angle Angle::operator/(const double & value)
{
  return Angle(data / value, is_degree);
}

double Angle::degree() const
{
  return is_degree ? data : scale_number(data, pi, 180.0);
}

double Angle::radian() const
{
  return is_degree ? scale_number(data, 180.0, pi) : data;
}

double Angle::normalized_degree() const
{
  return wrap_number(degree(), -180.0, 180.0);
}

double Angle::normalized_radian() const
{
  return wrap_number(radian(), -pi, pi);
}

}  // namespace keisan

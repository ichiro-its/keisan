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

#include "keisan/angle/angle.hpp"

namespace keisan
{

namespace literals
{

Angle<double> operator""_deg(unsigned long long int value)  // NOLINT
{
  return make_degree<double>(value);
}

Angle<double> operator""_deg(long double value)
{
  return make_degree<double>(value);
}

Angle<double> operator""_pi_rad(unsigned long long int value)  // NOLINT
{
  return make_radian<double>(value * pi<double>);
}

Angle<double> operator""_pi_rad(long double value)
{
  return make_radian<double>(value * pi<double>);
}

double wrap_rad(double value)
{
  return make_radian(value).normalize().radian();
}

double wrap_deg(double value)
{
  return make_degree(value).normalize().degree();
}

double rad_to_deg(double value)
{
  return make_radian(value).normalize().degree();
}

double deg_to_rad(double value)
{
  return make_degree(value).normalize().radian();
}

double delta_rad(double value1, double value2)
{
  return difference_between(make_radian(value1), make_radian(value2)).radian();
}

double delta_deg(double value1, double value2)
{
  return difference_between(make_degree(value1), make_degree(value2)).degree();
}

}  // namespace literals

}  // namespace keisan

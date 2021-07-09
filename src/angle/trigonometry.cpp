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
#include <keisan/angle/trigonometry.hpp>

namespace keisan
{

double sin(const Angle & angle)
{
  return std::sin(angle.radian());
}

double cos(const Angle & angle)
{
  return std::cos(angle.radian());
}

double tan(const Angle & angle)
{
  return std::tan(angle.radian());
}

Angle arcsin(const double & value)
{
  return make_radian(std::asin(value));
}

Angle arccos(const double & value)
{
  return make_radian(std::acos(value));
}

Angle arctan(const double & value)
{
  return make_radian(std::atan(value));
}

Angle signed_arctan(const double & y, const double & x)
{
  return make_radian(std::atan2(y, x));
}

}  // namespace keisan

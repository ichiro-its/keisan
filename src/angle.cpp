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

#include <keisan/angle.hpp>
#include <keisan/number.hpp>

namespace keisan
{

double wrap_rad(double value)
{
  return wrap_number(value, -pi, pi);
}

double wrap_deg(double value)
{
  return wrap_number(value, -180.0, 180.0);
}

double rad_to_deg(double value)
{
  return wrap_deg(scale_number(value, pi, 180.0));
}

double deg_to_rad(double value)
{
  return wrap_rad(scale_number(value, 180.0, pi));
}

double delta_deg(double value1, double value2)
{
  return wrap_deg(wrap_deg(value2) - wrap_deg(value1));
}

double delta_rad(double value1, double value2)
{
  return wrap_rad(wrap_rad(value2) - wrap_rad(value1));
}

}  // namespace keisan

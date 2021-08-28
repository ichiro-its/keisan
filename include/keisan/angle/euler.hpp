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

#ifndef KEISAN__ANGLE__EULER_HPP_
#define KEISAN__ANGLE__EULER_HPP_

#include <iostream>

#include "keisan/angle/angle.hpp"

namespace keisan
{

struct Euler;
struct Quaternion;

std::ostream & operator<<(std::ostream & out, const Euler & euler);

struct Euler
{
  Euler();
  Euler(const Angle<double> & roll, const Angle<double> & pitch, const Angle<double> & yaw);

  Euler(const Euler & other);

  Euler & operator=(const Euler & other);

  bool operator==(const Euler & other) const;
  bool operator!=(const Euler & other) const;

  Quaternion quaternion() const;

  Angle<double> roll;
  Angle<double> pitch;
  Angle<double> yaw;
};

}  // namespace keisan

#endif  // KEISAN__ANGLE__EULER_HPP_

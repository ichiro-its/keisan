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

#ifndef KEISAN__GEOMETRY__TRANSFORM2_HPP_
#define KEISAN__GEOMETRY__TRANSFORM2_HPP_

#include "../angle.hpp"
#include "../matrix.hpp"
#include "./point_2.hpp"

namespace keisan
{

class Transform2
{
public:
  Transform2();

  operator SquareMatrix<3>() const;

  Point2 operator*(const Point2 & point) const;

  void set_translation(const Point2 & translation);
  void set_rotation(const Angle<double> & rotation);

  void set_scale(const Point2 & scale);
  void set_scale(const double & scale);

  const Point2 & get_translation() const;
  const Angle<double> & get_rotation() const;
  const Point2 & get_scale() const;

private:
  Point2 translation;
  Angle<double> rotation;
  Point2 scale;
};

}  // namespace keisan

#endif   // KEISAN__GEOMETRY__TRANSFORM2_HPP_

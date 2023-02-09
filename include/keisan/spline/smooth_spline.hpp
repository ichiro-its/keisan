// Copyright (c) 2023 ICHIRO ITS
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

#ifndef KEISAN__SPLINE__SMOOTH_SPLINE_HPP_
#define KEISAN__SPLINE__SMOOTH_SPLINE_HPP_

#include "keisan/spline/spline.hpp"

namespace keisan
{

class SmoothSpline : public Spline
{
public:
  struct PointTime 
  {
    float point;
    float time;
  };

  SmoothSpline();
  SmoothSpline(std::vector<PointTime> point_times);
  ~SmoothSpline();

  void add_point(Polynom polynom);
  void add_point(double value, double t);
  Polynom polynomial_fit(double pos1, double pos2, double vel1, double vel2, double acc1, double acc2, double t);

private:
  std::vector<float> points;

};
}

#endif //KEISAN__SPLINE__SMOOTH_SPLINE_HPP_
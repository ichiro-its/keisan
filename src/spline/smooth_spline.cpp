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

#include "keisan/spline/smooth_spline.hpp"

namespace keisan
{

SmoothSpline::SmoothSpline()
{
}

SmoothSpline::~SmoothSpline()
{
}

SmoothSpline::SmoothSpline(std::vector<PointTime> point_times)
{
  for(auto point_time : point_times) {
    add_point(point_time.point, point_time.time);
  }
}

void SmoothSpline::add_point(Polynom polynom)
{
  splines.push_back(polynom);
}

void SmoothSpline::add_point(double value, double t)
{
  double pos1 = points.back();
  double pos2 = value;

  double acc1 = 0.0;
  double vel1 = 0.0;
  double acc2 = 0.0;
  double vel2 = 0.0;

  points.push_back(pos2);
  Polynom new_polynom = polynomial_fit(pos1, pos2, vel1, vel2, acc1, acc2, t);
  splines.push_back(new_polynom);
}

Polynom SmoothSpline::polynomial_fit(double pos1, double pos2, double vel1, double vel2, double acc1, double acc2, double t)
{
  double t2 = t * t;
  double t3 = t2 * t;
  double t4 = t3 * t;
  double t5 = t4 * t;

  std::vector<double> coefficients;
  coefficients.resize(6);
  coefficients[0] = pos1;
  coefficients[1] = vel1;
  coefficients[2] = acc1 / 2;
  coefficients[3] = -(-acc2 * t2 + 3 * acc1 * t2 + 8 * vel2 * t + 12 * vel1 * t - 20 * pos2 + 20 * pos1) / (2 * t3);
  coefficients[4] = (-2 * acc2 * t2 + 3 * acc1 * t2 + 14 * vel2 * t + 16 * vel1 * t - 30 * pos2 + 30 * pos1) / (2 * t4);
  coefficients[5] = -(-acc2 * t2 + acc1 * t2 + 6 * vel2 * t + 6 * vel1 * t - 12 * pos2 + 12 * pos1) / (2 * t5);

  Polynom polynom(coefficients); 
  return polynom;
}

}

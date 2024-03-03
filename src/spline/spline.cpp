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

#include <vector>

#include "keisan/spline/spline.hpp"

namespace keisan
{

Spline::Spline()
{
}

Spline::~Spline()
{
}

std::vector<Polynom> Spline::get_splines()
{
  return splines;
}

void Spline::add_spline(const Polynom& polynom)
{
  splines.push_back(polynom);
}

double Spline::interpolate_value(double value, int derivative_order)
{
  int start_index = 0;
  int end_index = splines.size() - 1;
  Polynom center_spline = splines[0];
  while (start_index != end_index) {
    int center_index = (start_index + end_index) / 2;
    center_spline = splines[center_index];

    if (value < center_spline.min_value) {
      end_index = center_index - 1;
      continue;
    }
    if (value > center_spline.max_value) {
      start_index = center_index + 1;
      continue;
    }
    start_index = center_index;
    end_index = center_index;
  }

  return center_spline.get_value(value - center_spline.min_value, derivative_order);
}

}

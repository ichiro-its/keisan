// Copyright (c) 2024 ICHIRO ITS
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

#ifndef KEISAN__INTERPOLATION__SPLINE_HPP_
#define KEISAN__INTERPOLATION__SPLINE_HPP_

#include "keisan/interpolation/polynom.hpp"

namespace keisan
{

class Spline
{
public:
  Spline(const std::vector<Polynom> & polynoms);

  double operator()(const double & x) const;

  Spline derivative() const;

private:
  std::vector<Polynom> polynoms;
};

Spline linear_spline(const std::vector<double> & x, const std::vector<double> & y);
Spline quadratic_spline(const std::vector<double> & x, const std::vector<double> & y);
Spline cubic_spline(const std::vector<double> & x, const std::vector<double> & y);

}  // namespace keisan

#include "keisan/interpolation/spline.impl.hpp"

#endif  // KEISAN__INTERPOLATION__SPLINE_HPP_

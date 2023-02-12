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

#include <vector>

#include "keisan/spline/polynom.hpp"

namespace keisan
{

Polynom::Polynom()
{
}

Polynom::Polynom(const std::vector<double> & coefficients)
: coefs(coefficients)
{
}

double Polynom::get_value(double value)
{
  return get_value(value, OrderType::POSITION);
}

double Polynom::get_value(double value, int derivative_order)
{
  double xx = 1.0;
  double val = 0.0;
  for (int i = derivative_order; i < coefs.size(); i++) {
    double multiplicand = xx * coefs[i];
    for (int j = 0; j < derivative_order; j++) {
      multiplicand *= (i - j - 1);
    }
    val += multiplicand;
    xx *= value;
  }
  return val;
}

}

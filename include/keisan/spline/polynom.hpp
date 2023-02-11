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

#ifndef KEISAN__SPLINE__POLYNOM_HPP_
#define KEISAN__SPLINE__POLYNOM_HPP_

#include <ostream>
#include <vector>

namespace keisan
{

class Polynom
{
public:
  Polynom();
  Polynom(const std::vector<double> & coefficients);

  double get_value(double value);
  double get_value(double value, int derivative_order);

  enum OrderType {
    POSITION = 0,
    VELOCITY = 1,
    ACCELERATION = 2,
    JERK = 3
  };

  double min_value;
  double max_value;
private:
  std::vector<double> coefs;
};

} // namespace keisan

#endif // KEISAN__SPLINE__POLYNOM_HPP_

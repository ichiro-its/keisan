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

#ifndef KEISAN__INTERPOLATION__POLYNOM_HPP_
#define KEISAN__INTERPOLATION__POLYNOM_HPP_

#include <vector>

namespace keisan
{

class Polynom
{
public:
  Polynom(
    const std::vector<double> & coefficients = {0.0}, const double & domain_min = 0.0,
    const double & domain_max = 0.0);

  bool is_in_domain(const double & x) const;

  double operator()(const double & x) const;

  bool operator==(const Polynom & other) const;
  bool operator!=(const Polynom & other) const;

  Polynom operator+(const Polynom & other) const;
  Polynom operator-(const Polynom & other) const;

  Polynom derivative() const;

  Polynom integral() const;

private:
  std::vector<double> coefficients;
  double domain_min;
  double domain_max;
};

}  // namespace keisan

#include "keisan/interpolation/polynom.impl.hpp"

#endif  // KEISAN__INTERPOLATION__POLYNOM_HPP_

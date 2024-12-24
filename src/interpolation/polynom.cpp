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

#include <cmath>

#include "keisan/interpolation/polynom.hpp"

namespace keisan
{

Polynom::Polynom(const std::vector<double> & coefficients)
: coefficients(coefficients)
{}

double Polynom::operator()(const double & x) const
{
  double result = 0.0;

  for (size_t i = 0; i < coefficients.size(); ++i) {
    result += coefficients[i] * std::pow(x, i);
  }

  return result;
}

Polynom Polynom::derivative() const
{
  std::vector<double> new_coefficients;

  for (size_t i = 1; i < coefficients.size(); ++i) {
    new_coefficients.push_back(i * coefficients[i]);
  }

  return Polynom(new_coefficients);
}

Polynom Polynom::integral() const
{
  std::vector<double> new_coefficients;

  new_coefficients.push_back(0.0);

  for (size_t i = 0; i < coefficients.size(); ++i) {
    new_coefficients.push_back(coefficients[i] / (i + 1));
  }

  return Polynom(new_coefficients);
}

} // namespace keisan

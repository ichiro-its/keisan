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

#ifndef KEISAN__INTERPOLATION__POLYNOM_IMPL_HPP_
#define KEISAN__INTERPOLATION__POLYNOM_IMPL_HPP_

#include <cmath>

#include "keisan/interpolation/polynom.hpp"

namespace keisan
{

Polynom::Polynom(const std::vector<double> & coefficients, double domain_min, double domain_max)
: coefficients(coefficients), domain_min(domain_min), domain_max(domain_max)
{
}

bool Polynom::is_in_domain(double x) const { return x >= domain_min && x <= domain_max; }

double Polynom::operator()(double x) const
{
  double result = 0.0;

  for (size_t i = 0; i < coefficients.size(); ++i) {
    result += coefficients[i] * std::pow(x - domain_min, i);
  }

  return result;
}

bool Polynom::operator==(const Polynom & other) const
{
  return coefficients == other.coefficients && domain_min == other.domain_min &&
         domain_max == other.domain_max;
}

bool Polynom::operator!=(const Polynom & other) const { return !(*this == other); }

Polynom Polynom::operator+(const Polynom & other) const
{
  std::vector<double> new_coefficients(std::max(coefficients.size(), other.coefficients.size()));

  for (size_t i = 0; i < std::max(coefficients.size(), other.coefficients.size()); ++i) {
    double a = (i < coefficients.size()) ? coefficients[i] : 0.0;
    double b = (i < other.coefficients.size()) ? other.coefficients[i] : 0.0;

    new_coefficients[i] = a + b;
  }

  return Polynom(new_coefficients, domain_min, domain_max);
}

Polynom Polynom::operator-(const Polynom & other) const
{
  std::vector<double> new_coefficients(std::max(coefficients.size(), other.coefficients.size()));

  for (size_t i = 0; i < std::max(coefficients.size(), other.coefficients.size()); ++i) {
    double a = (i < coefficients.size()) ? coefficients[i] : 0.0;
    double b = (i < other.coefficients.size()) ? other.coefficients[i] : 0.0;

    new_coefficients[i] = a - b;
  }

  return Polynom(new_coefficients, domain_min, domain_max);
}

Polynom Polynom::derivative() const
{
  std::vector<double> new_coefficients(coefficients.size() > 1 ? coefficients.size() - 1 : 0);

  for (size_t i = 1; i < coefficients.size(); ++i) {
    new_coefficients[i - 1] = i * coefficients[i];
  }

  return Polynom(new_coefficients, domain_min, domain_max);
}

Polynom Polynom::integral() const
{
  std::vector<double> new_coefficients(coefficients.size() + 1);

  new_coefficients[0] = 0.0;

  for (size_t i = 0; i < coefficients.size(); ++i) {
    new_coefficients[i + 1] = coefficients[i] / (i + 1);
  }

  return Polynom(new_coefficients, domain_min, domain_max);
}

std::ostream & operator<<(std::ostream & os, const Polynom & polynom)
{
  for (size_t i = polynom.coefficients.size(); i-- > 0;) {
    os << polynom.coefficients[i];

    if (i > 0) {
      os << "x^" << i;
    }

    if (i != 0) {
      os << " + ";
    }
  }
  os << ", Domain: [" << polynom.domain_min << ", " << polynom.domain_max << "]";
  return os;
};

}  // namespace keisan

#endif  // KEISAN__INTERPOLATION__POLYNOM_IMPL_HPP_

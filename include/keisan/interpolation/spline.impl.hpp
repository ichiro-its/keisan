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

#ifndef KEISAN__INTERPOLATION__SPLINE_IMPL_HPP_
#define KEISAN__INTERPOLATION__SPLINE_IMPL_HPP_

#include <stdexcept>

#include "keisan/interpolation/spline.hpp"

namespace keisan
{

Spline::Spline(const std::vector<Polynom> & polynoms)
{
  if (polynoms.size() < 2) {
    throw std::invalid_argument("The spline must have at least two polynom!");
  }

  this->polynoms = polynoms;
}

double Spline::operator()(double x) const
{
  for (const auto & polynom : polynoms) {
    if (polynom.is_in_domain(x)) {
      return polynom(x);
    }
  }

  throw std::out_of_range("The x value is out of range!");
}

Spline Spline::derivative() const
{
  std::vector<Polynom> new_polynoms;

  for (const auto & polynom : polynoms) {
    new_polynoms.push_back(polynom.derivative());
  }

  return Spline(new_polynoms);
}

std::vector<Polynom> Spline::get_polynoms() const { return polynoms; }

}  // namespace keisan

#endif  // KEISAN__INTERPOLATION__SPLINE_IMPL_HPP_

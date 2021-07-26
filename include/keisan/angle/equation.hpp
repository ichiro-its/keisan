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

#ifndef KEISAN__ANGLE__EQUATION_HPP_
#define KEISAN__ANGLE__EQUATION_HPP_

#include "./angle.hpp"

namespace keisan
{

[[deprecated("Use Angle::normalized_radian() instead.")]]
double wrap_rad(double value);

[[deprecated("Use Angle::normalized_degree() instead.")]]
double wrap_deg(double value);

[[deprecated("Use Angle::degree() instead.")]]
double rad_to_deg(double value);

[[deprecated("Use Angle::radian() instead.")]]
double deg_to_rad(double value);

[[deprecated("Use difference_between() instead.")]]
double delta_rad(double value1, double value2);

[[deprecated("Use difference_between() instead.")]]
double delta_deg(double value1, double value2);

}  // namespace keisan

#endif  // KEISAN__ANGLE__EQUATION_HPP_

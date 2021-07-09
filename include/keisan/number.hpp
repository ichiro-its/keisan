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

#ifndef KEISAN__NUMBER_HPP_
#define KEISAN__NUMBER_HPP_

namespace keisan
{

double sign(const double & value);

double scale(const double & value, const double & source, const double & target);

double map(
  const double & value, const double & source_min, const double & source_max,
  const double & target_min, const double & target_max);

double clamp(const double & value, const double & min, const double & max);
double wrap(const double & value, const double & min, const double & max);

[[deprecated("Use sign() instead.")]]
double sign_number(double value);

[[deprecated("Use scale() instead.")]]
double scale_number(double value, double source, double target);

[[deprecated("Use map() instead.")]]
double map_number(
  double value, double source_min, double source_max, double target_min, double target_max);

[[deprecated("Use clamp() instead.")]]
double clamp_number(double value, double min, double max);

[[deprecated("Use wrap() instead.")]]
double wrap_number(double value, double min, double max);

}  // namespace keisan

#endif  // KEISAN__NUMBER_HPP_

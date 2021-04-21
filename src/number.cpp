// Copyright (c) 2021 Ichiro ITS
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

#include <keisan/number.hpp>

#include <algorithm>
#include <cmath>

namespace keisan
{

double wrap_number(double value, double min, double max)
{
  double min_value = value - min;
  double min_max = max - min;

  return min + fmod(min_max + fmod(min_value, min_max), min_max);
}

double scale_number(double value, double source, double target)
{
  return value * target / source;
}

double map_number(
  double value, double source_min, double source_max, double target_min, double target_max)
{
  return target_min + scale_number(
    value - source_min, source_max - source_min, target_max - target_min);
}

double clamp_number(double value, double min_value, double max_value)
{
  return std::max(std::min(value, max_value), min_value);
}

}  // namespace keisan

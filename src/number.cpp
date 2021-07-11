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

#include <keisan/number.hpp>

#include <algorithm>
#include <cmath>

namespace keisan
{

double sign(const double & value)
{
  return (value >= 0) ? 1.0 : -1.0;
}

double scale(const double & value, const double & source, const double & target)
{
  return value * target / source;
}

double map(
  const double & value, const double & source_min, const double & source_max,
  const double & target_min, const double & target_max)
{
  return target_min + scale(value - source_min, source_max - source_min, target_max - target_min);
}

double clamp(const double & value, const double & min, const double & max)
{
  return std::min(std::max(value, min), max);
}

double wrap(const double & value, const double & min, const double & max)
{
  double min_value = value - min;
  double min_max = max - min;

  return min + std::fmod(min_max + std::fmod(min_value, min_max), min_max);
}

double sign_number(double value)
{
  return sign(value);
}

double scale_number(double value, double source, double target)
{
  return scale(value, source, target);
}

double map_number(
  double value, double source_min, double source_max, double target_min, double target_max)
{
  return map(value, source_min, source_max, target_min, target_max);
}

double clamp_number(double value, double min, double max)
{
  return clamp(value, min, max);
}

double wrap_number(double value, double min, double max)
{
  return wrap(value, min, max);
}

}  // namespace keisan

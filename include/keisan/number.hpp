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

#include <algorithm>
#include <cmath>
#include <type_traits>

namespace keisan
{

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
sign(const T & value)
{
  return (value >= 0) ? 1 : -1;
}

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
scale(const T & value, const T & source, const T & target)
{
  return value / source * target;
}

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
map(
  const T & value, const T & source_min, const T & source_max,
  const T & target_min, const T & target_max)
{
  return target_min + scale(value - source_min, source_max - source_min, target_max - target_min);
}

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
clamp(const T & value, const T & min, const T & max)
{
  return std::min(std::max(value, min), max);
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type
wrap(const T & value, const T & min, const T & max)
{
  auto min_value = value - min;
  auto min_max = max - min;

  return min + std::fmod(min_max + std::fmod(min_value, min_max), min_max);
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type
wrap(const T & value, const T & min, const T & max)
{
  auto min_value = value - min;
  auto min_max = max - min;

  return min + (min_max + min_value % min_max) % min_max;
}

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

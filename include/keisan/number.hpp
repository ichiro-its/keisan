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

namespace keisan
{
template<typename T>
T wrap_number(T value, T min, T max)
{
  T min_value = value - min;
  T min_max = max - min;

  return min + fmod(min_max + fmod(min_value, min_max), min_max);
}

template<typename T>
T scale_number(T value, T source, T target)
{
  return value * target / source;
}

template<typename T>
T map_number(
  T value, T source_min, T source_max, T target_min, T target_max)
{
  return target_min + scale_number(
    value - source_min, source_max - source_min, target_max - target_min);
}

template<typename T>
T clamp_number(T value, T min_value, T max_value)
{
  return std::max(std::min(value, max_value), min_value);
}

template<typename T>
T sign_number(T value)
{
  return (value >= 0) ? 1.0 : -1.0;
}

}  // namespace keisan

#endif  // KEISAN__NUMBER_HPP_

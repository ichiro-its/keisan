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
template<typename M, typename N, typename O>
M wrap_number(M value, N min, O max)
{
  M min_value = value - min;
  M min_max = max - min;

  return min + fmod(min_max + fmod(min_value, min_max), min_max);
}

template<typename M, typename N, typename O>
M scale_number(M value, N source, O target)
{
  return value * target / source;
}

template<typename M, typename N, typename O, typename P, typename Q>
M map_number(
  M value, N source_min, O source_max, P target_min, Q target_max)
{
  return target_min + scale_number(
    value - source_min, source_max - source_min, target_max - target_min);
}

template<typename M, typename N, typename O>
M clamp_number(M value, N min_value, O max_value)
{
  return std::max(std::min(value, max_value), min_value);
}

template<typename M>
M sign_number(M value)
{
  return (value >= 0) ? 1.0 : -1.0;
}

}  // namespace keisan

#endif  // KEISAN__NUMBER_HPP_

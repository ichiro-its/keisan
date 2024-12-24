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

#include "keisan/interpolation/spline.hpp"

namespace keisan
{

Spline linear_spline(const std::vector<double> & x, const std::vector<double> & y)
{
  std::vector<Polynom> polynoms;

  for (size_t i = 0; i < x.size() - 1; ++i) {
    double a = (y[i + 1] - y[i]) / (x[i + 1] - x[i]);
    double b = y[i] - a * x[i];

    polynoms.push_back(Polynom({b, a}, x[i], x[i + 1]));
  }

  return Spline(polynoms);
}

Spline quadratic_spline(const std::vector<double> & x, const std::vector<double> & y)
{
  std::vector<Polynom> polynoms;

  for (size_t i = 0; i < x.size() - 1; ++i) {
    double a = ((y[i + 1] - y[i]) / (x[i + 1] - x[i]) - (y[i] - y[i - 1]) / (x[i] - x[i - 1])) /
               (x[i + 1] - x[i - 1]);
    double b = (y[i] - y[i - 1]) / (x[i] - x[i - 1]) - a * x[i];
    double c = y[i] - a * x[i] * x[i] - b * x[i];

    polynoms.push_back(Polynom({c, b, a}, x[i], x[i + 1]));
  }

  return Spline(polynoms);
}

Spline cubic_spline(const std::vector<double> & x, const std::vector<double> & y)
{
  std::vector<Polynom> polynoms;

  std::vector<double> h;
  std::vector<double> a;
  std::vector<double> b;
  std::vector<double> c;
  std::vector<double> d;

  for (size_t i = 0; i < x.size() - 1; ++i) {
    h.push_back(x[i + 1] - x[i]);
    a.push_back(y[i]);
  }

  std::vector<double> alpha;
  for (size_t i = 1; i < x.size() - 1; ++i) {
    alpha.push_back(3.0 / h[i] * (a[i + 1] - a[i]) - 3.0 / h[i - 1] * (a[i] - a[i - 1]));
  }

  std::vector<double> l(x.size(), 1.0);
  std::vector<double> mu(x.size(), 0.0);
  std::vector<double> z(x.size(), 0.0);

  for (size_t i = 1; i < x.size() - 1; ++i) {
    l[i] = 2.0 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
    mu[i] = h[i] / l[i];
    z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
  }

  for (size_t i = x.size() - 2; i > 0; --i) {
    c.push_back(z[i] - mu[i] * c.back());
    b.push_back((a[i + 1] - a[i]) / h[i] - h[i] * (c.back() + 2.0 * c.back()) / 3.0);
    d.push_back((c.back() - c.back()) / (3.0 * h[i]));
  }

  for (size_t i = 0; i < x.size() - 1; ++i) {
    polynoms.push_back(Polynom({a[i], b[i], c[i], d[i]}, x[i], x[i + 1]));
  }

  return Spline(polynoms);
}

}  // namespace keisan

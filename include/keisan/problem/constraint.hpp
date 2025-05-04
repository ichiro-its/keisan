// Copyright (c) 2025 ICHIRO ITS
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

#ifndef KEISAN__PROBLEM__CONSTRAINT_HPP_
#define KEISAN__PROBLEM__CONSTRAINT_HPP_

#include "keisan/problem/expression.hpp"

#include <Eigen/Dense>

#include <string>

namespace keisan
{

class Constraint
{
public:
  enum Priority
  {
    Soft,  // Constraint tidak harus diselesaikan, seberapa dekat tergantung dengan weight.
    Hard   // Constraint harus diselesaikan, jika tidak, akan keluar error.
  };

  enum Type
  {
    Equality,
    Inequality
  };

  Expression expression;

  Type type = Equality;
  Priority priority = Hard;

  double weight = 1.0;

  bool is_active = false;

  void configure(Priority priority_, double weight_ = 1.0);
  void configure(std::string type_, double weight_ = 1.0);

  bool operator==(const Constraint & other) const;
};

}  // namespace keisan

#endif  // KEISAN__PROBLEM__CONSTRAINT_HPP_

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

#ifndef KEISAN__PROBLEM__EXPRESSION_HPP_
#define KEISAN__PROBLEM__EXPRESSION_HPP_

#include <Eigen/Dense>

namespace keisan
{

class Constraint;

/**
 * Expression yang dimaksud adalah kombinasi linier dari decision variables dalam bentuk Ax + b
 */
class Expression
{
public:
  Expression();
  Expression(const Expression & other);
  Expression(const Eigen::VectorXd & v);

  Eigen::MatrixXd A = Eigen::MatrixXd(0, 0);
  Eigen::VectorXd b = Eigen::VectorXd(0);

  Expression slice(int start, int rows = -1) const;

  static Expression from_vector(const Eigen::VectorXd & v);
  static Expression from_double(const double & value);

  Eigen::VectorXd value(Eigen::VectorXd x) const;

  bool is_scalar() const;
  bool is_constant() const;

  int cols() const;
  int rows() const;

  Expression piecewise_add(double f) const;
  Expression left_multiply(const Eigen::MatrixXd M);
  Expression sum();
  Expression mean();

  Expression operator+(const Expression & other) const;
  Expression operator-(const Expression & other) const;
  Expression operator-() const;

  Expression operator*(double f) const;
  friend Expression operator*(double f, const Expression & e);
  Expression operator*(const Expression & other) const;

  Expression operator+(const Eigen::VectorXd v) const;
  friend Expression operator+(const Eigen::VectorXd v, const Expression & e);
  Expression operator-(const Eigen::VectorXd v) const;
  friend Expression operator-(const Eigen::VectorXd v, const Expression & e);

  Expression operator+(const double f) const;
  friend Expression operator+(double, const Expression & e);
  Expression operator-(const double f) const;
  friend Expression operator-(double, const Expression & e);

  friend Expression operator*(const Eigen::MatrixXd M, const Expression & e);

  Expression operator/(const Expression & other) const;

  Constraint operator>=(const Expression & other) const;
  Constraint operator<=(const Expression & other) const;

  Constraint operator>=(double f) const;
  friend Constraint operator>=(double f, const Expression & e);

  Constraint operator<=(double f) const;
  friend Constraint operator<=(double f, const Expression & e);

  Constraint operator>=(Eigen::VectorXd v) const;
  friend Constraint operator>=(Eigen::VectorXd v, const Expression & e);

  Constraint operator<=(Eigen::VectorXd v) const;
  friend Constraint operator<=(Eigen::VectorXd v, const Expression & e);

  Constraint operator==(const Expression & other) const;
  Constraint operator==(Eigen::VectorXd v) const;

  friend Constraint operator==(Eigen::VectorXd v, const Expression & e);

  Constraint operator==(double f) const;
  friend Constraint operator==(double f, const Expression & e);
};

}  // namespace keisan

#endif  // KEISAN__PROBLEM__EXPRESSION_HPP_

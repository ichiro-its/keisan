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

#ifndef EKF_BALL_HPP
#define EKF_BALL_HPP

#include "keisan/matrix.hpp"

namespace keisan
{

class ekf_ball
{
public:
    ekf_ball();

    void init(double x, double y);
    void predict(double dt);
    void update(const Matrix<2, 1> & z);

    Matrix<2, 1> getPosition() const;
    Matrix<2, 1> getVelocity() const;

    Matrix<4, 1> getState() const;
    Matrix<4, 4> getCovariance() const;

private:
    Matrix<4, 1> X_;
    Matrix<4, 4> P_;
    Matrix<4, 4> Q_;
    Matrix<2, 2> R_;
};

}  // namespace keisan

#endif  // EKF_BALL_HPP

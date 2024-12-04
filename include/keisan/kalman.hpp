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

#ifndef KEISAN__KEISAN_HPP_
#define KEISAN__KEISAN_HPP_

#include "keisan/matrix.hpp"

namespace keisan
{

class Kalman
{
public:
  Kalman(float dt, float std_dev_aceleration, Matrix<2, 1> std_measurement, Matrix<2, 1> acceleration); 
  Matrix<4, 1> predict();
  Matrix<4, 1> update(Matrix<2, 1> measurement);

private:
    Matrix<4, 1> Xk;
    Matrix<4, 4> Q;
    Matrix<2, 2> R;
    Matrix<4, 4> A;
    Matrix<4, 2> B;
    Matrix<4, 4> P;
    Matrix<2, 4> H;
    Matrix<2, 1> U; 
};

} // namespace keisa

#endif // KEISAN__KEISAN_HPP_
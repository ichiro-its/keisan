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

#include "gtest/gtest.h"
#include "keisan/keisan.hpp"

namespace ksn = keisan;

using ksn::literals::operator""_deg;

TEST(NumberTest, SignIntegral)
{
  EXPECT_EQ(ksn::sign(0), 1) << "Sign result must be positive for zero";
  EXPECT_EQ(ksn::sign(5), 1) << "Sign result must be positive";
  EXPECT_EQ(ksn::sign(-5), -1) << "Sign result must be negative";
}

TEST(NumberTest, SignFloatingPoint)
{
  EXPECT_DOUBLE_EQ(ksn::sign(0.0), 1.0) << "Sign result must be positive for zero";
  EXPECT_DOUBLE_EQ(ksn::sign(5.0), 1.0) << "Sign result must be positive";
  EXPECT_DOUBLE_EQ(ksn::sign(-5.0), -1.0) << "Sign result must be negative";
}

TEST(NumberTest, SignAngle)
{
  EXPECT_DOUBLE_EQ(ksn::sign(ksn::make_degree(0)), 1.0) << "Sign result must be positive for zero";
  EXPECT_DOUBLE_EQ(ksn::sign(ksn::make_degree(90)), 1.0) << "Sign result must be positive";
  EXPECT_DOUBLE_EQ(ksn::sign(ksn::make_degree(-900)), -1.0) << "Sign result must be negative";
}

TEST(NumberTest, ScaleIntegral)
{
  EXPECT_EQ(ksn::scale(5, 2, 3), 6) << "5 / 2 = 2\n"
                                       "2 * 3 = 6";
}

TEST(NumberTest, ScaleFloatingPoint)
{
  EXPECT_DOUBLE_EQ(ksn::scale(3.3, 0.5, 1.5), 9.9) << "3.3 / 0.5 = 6.6\n"
                                                      "6.6 * 1.5 = 9.9";
}

TEST(NumberTest, MapIntegral)
{
  EXPECT_EQ(ksn::map(5, 2, 4, 0, 1), 1) << "min(5, max(2, 4)) = 4\n"
                                           "max(4, min(2, 4)) = 4\n"
                                           "4 - 2 = 2\n"
                                           "4 - 2 = 2\n"
                                           "1 - 0 = 1\n"
                                           "scale(2, 2, 1) = 1\n"
                                           "1 + 0 = 1";

  EXPECT_EQ(ksn::map(0, -2, -4, 0, 1), 0) << "min(0, max(-2, -4)) = -2\n"
                                             "max(-2, min(-2, -4)) = -2\n"
                                             "-2 - (-2) = 0\n"
                                             "-4 - (-2) = -2\n"
                                             "1 - 0 = 1\n"
                                             "scale(0, -2, 1) = 0\n"
                                             "0 + 0 = 0";

  EXPECT_EQ(ksn::map(10, 3, 11, -2, 2), -2) << "min(10, max(3, 11)) = 10\n"
                                               "max(10, min(3, 11)) = 10\n"
                                               "10 - 3 = 7\n"
                                               "11 - 3 = 8\n"
                                               "2 - (-2) = 4\n"
                                               "scale(7, 8, 4) = 0\n"
                                               "0 + (-2) = -2";
}

TEST(NumberTest, MapFloatingPoint)
{
  EXPECT_DOUBLE_EQ(ksn::map(0.5, 0.2, 0.8, 1.0, 3.2), 2.1) << "min(0.5, max(0.2, 0.8)) = 0.5\n"
                                                              "max(0.5, min(0.2, 0.8)) = 0.5\n"
                                                              "0.5 - 0.2 = 0.3\n"
                                                              "0.8 - 0.2 = 0.6\n"
                                                              "3.2 - 1.0 = 2.2\n"
                                                              "scale(0.5, 0.6, 2.2) = 1.1\n"
                                                              "1.1 + 1.0 = 2.1";

  EXPECT_DOUBLE_EQ(ksn::map(-0.1, 0.2, 0.8, -3.2, -1.0), -3.2)
    << "min(-0.1, max(0.2, 0.8)) = -0.1\n"
       "max(-0.1, min(0.2, 0.8)) = 0.2\n"
       "0.2 - 0.2 = 0.0\n"
       "0.8 - 0.2 = 0.6\n"
       "-1.0 - (-3.2) = 2.2\n"
       "scale(0.0, 0.6, 2.2) = 0.0\n"
       "0.0 + (-3.2) = -3.2";

  EXPECT_DOUBLE_EQ(ksn::map(-1.5, 5.0, -2.5, 7.0, 13.0), 12.2)
    << "min(-1.5, max(5.0, -2.5)) = -1.5\n"
       "max(-1.5, min(5.0, -2.5)) = -1.5\n"
       "-1.5 - 5.0 = -6.5\n"
       "-2.5 - 5.0 = -7.5\n"
       "13.0 - 7.0 = 6.0\n"
       "scale(-6.5, -7.5, 6.0) = 5.2\n"
       "5.2 + 7.0 = 12.2";
}

TEST(NumberTest, ExponentialMapIntegral)
{
  EXPECT_EQ(ksn::exponentialmap(5, 2, 4, 0, 1), 1) << "clamp(5, 2, 4) = 4\n"
                                                      "map_coeff (0 <= 1) = 1\n"
                                                      "normalized_val = (4 - 2)/(4 - 2) = 1\n"
                                                      "1 * pow(|1 - 0 + 1|, 1) + 0 - 1 = 1\n";

  EXPECT_EQ(ksn::exponentialmap(-5, -4, -2, 0, 1), 0)
    << "clamp(-5, -4, -2) = -4\n"
       "map_coeff (0 <= 1) = 1\n"
       "normalized_val = (-4 - (-4))/( -2 - (-4)) = 0\n"
       "1 * pow(|1 - 0 + 1|, 0) + 0 - 1 = 0\n";
}

TEST(NumberTest, ExponentialMapFloatingPoint)
{
  EXPECT_DOUBLE_EQ(ksn::exponentialmap(5.2, 1.8, 4.9, 0.4, 2.4), 2.4)
    << "clamp(5.2, 1.8, 4.9) = 4.9\n"
       "map_coeff (0.4 <= 2.4) = 1\n"
       "normalized_val = (4.9 - 1.8) / (4.9 - 1.8) = 1\n"
       "1 * pow(|2.4 - 0.4 + 1|, 1) + 0.4 - 1 = 2.4\n";

  EXPECT_DOUBLE_EQ(ksn::exponentialmap(-6.9, -4.2, -2.0, 0.0, 1.3), 0)
    << "clamp(-6.9, -4.2, -2.0) = -4.2\n"
       "map_coeff (0.0 <= 1.3) = 1\n"
       "normalized_val = (-4.2 - (-4.2)) / (-2.0 - (-4.2)) = 0\n"
       "1 * pow(|1.3 - 0.0 + 1|, 0) + 0.0 - 1 = 0\n";

  EXPECT_NEAR(ksn::exponentialmap(10.2, 3.1, 14.7, -2.2, 2.2), -0.393, 0.001)
    << "clamp(10.2, 3.1, 14.7) = 10.2\n"
       "map_coeff (-2.2 <= 2.2) = 1\n"
       "normalized_val = (10.2 - 3.1) / (14.7 - 3.1) = 0.6121\n"
       "1 * pow(|2.2 - (-2.2) + 1|, 0.6121) + (-2.2) - 1 ~ -0.393\n";

  EXPECT_NEAR(ksn::exponentialmap(10.2, 3.1, 14.7, 2.2, -2.2), 0.393, 0.001)
    << "clamp(10.2, 3.1, 14.7) = 10.2\n"
       "map_coeff (2.2 <= -2.2) = -1\n"
       "normalized_val = (10.2 - 3.1) / (14.7 - 3.1) = 0.6121\n"
       "-1 * pow(|-2.2 - 2.2 + (-1)|, 0.6121) + 2.2 - (-1) ~ 0.393\n";

  EXPECT_NEAR(ksn::exponentialmap(10.2, 14.7, 3.1, 2.2, -2.2), 1.276, 0.001)
    << "clamp(10.2, 14.7, 3.1) = 10.2\n"
       "map_coeff (2.2 <= -2.2) = -1\n"
       "normalized_val = (10.2 - 14.7) / (3.1 - 14.7) = 0.3879\n"
       "-1 * pow(|-2.2 - 2.2 + (-1)|, 0.3879) + 2.2 - (-1) ~ 1.276\n";

  EXPECT_NEAR(ksn::exponentialmap(10.2, 14.7, 3.1, -2.2, 2.2), -1.276, 0.001)
    << "clamp(10.2, 14.7, 3.1) = 10.2\n"
       "map_coeff (-2.2 <= 2.2) = 1\n"
       "normalized_val = (10.2 - 14.7) / (3.1 - 14.7) = 0.3879\n"
       "1 * pow(|2.2 - (-2.2) + 1|, 0.3879) + (-2.2) - 1 ~ -1.276\n";
}

TEST(NumberTest, SinusoidalMapIntegral)
{
  EXPECT_EQ(ksn::sinusoidalmap(10, 2, 4, 0, 2), 2) << "clamp(10, 2, 4) = 4\n"
                                                      "coeff = -(2 - 0) / 2 = -1\n"
                                                      "angle = (M_PI * (2 - 4)) / (2 - 4) = M_PI\n"
                                                      "-1 * cos(M_PI) + (2 + 0) / 2 = 2\n";

  EXPECT_EQ(ksn::sinusoidalmap(-5, -4, -2, 0, 1), 0)
    << "clamp(-5, -4, -2) = -4\n"
       "coeff = -(1 - 0) / 2 = -0.5\n"
       "angle = (M_PI * (-4 - (-4))) / (-4 - (-2)) = 0\n"
       "-0.5 * cos(0) + (1 + 0) / 2 = 0\n";
}

TEST(NumberTest, SinusoidalMapFloatingPoint)
{
  EXPECT_DOUBLE_EQ(ksn::sinusoidalmap(5.2, 1.8, 4.9, 0.4, 2.4), 2.4)
    << "clamp(5.2, 1.8, 4.9) = 4.9\n"
       "coeff = -(2.4 - 0.4) / 2 = -1\n"
       "angle = (M_PI * (1.8 - 4.9)) / (1.8 - 4.9) = M_PI\n"
       "-1 * cos(M_PI) + (2.4 + 0.4) / 2 = 2.4\n";

  EXPECT_DOUBLE_EQ(ksn::sinusoidalmap(-6.9, -4.2, -2.0, 0.0, 1.3), 0)
    << "clamp(-6.9, -4.2, -2.0) = -4.2\n"
       "coeff = -(1.3 - 0.0) / 2 = -0.65\n"
       "angle = (M_PI * (-4.2 - (-4.2))) / (-4.2 - (-2.0)) = 0\n"
       "-0.65 * cos(0) + (1.3 + 0.0) / 2 = 0.0\n";

  EXPECT_NEAR(ksn::sinusoidalmap(10.2, 3.1, 14.7, -2.2, 2.2), 0.759, 0.001)
    << "clamp(10.2, 3.1, 14.7) = 10.2\n"
       "coeff = -(2.2 - (-2.2)) / 2 = -2.2\n"
       "angle = (M_PI * (3.1 - 10.2)) / (3.1 - 14.7) ~ 1.923\n"
       "-2.2 * cos(1.923) + (2.2 + (-2.2)) / 2 ~ 0.759\n";

  EXPECT_NEAR(ksn::sinusoidalmap(10.2, 3.1, 14.7, 2.2, -2.2), -0.759, 0.001)
    << "clamp(10.2, 3.1, 14.7) = 10.2\n"
       "coeff = -(-2.2 - 2.2) / 2 = 2.2\n"
       "angle = (M_PI * (3.1 - 10.2)) / (3.1 - 14.7) ~ 1.923\n"
       "2.2 * cos(1.923) + (-2.2 + 2.2) / 2 ~ -0.759\n";

  EXPECT_NEAR(ksn::sinusoidalmap(10.2, 14.7, 3.1, 2.2, -2.2), 0.759, 0.001)
    << "clamp(10.2, 14.7, 3.1) = 10.2\n"
       "coeff = -(-2.2 - 2.2) / 2 = 2.2\n"
       "angle = (M_PI * (14.7 - 10.2)) / (14.7 - 3.1) = 1.219\n"
       "2.2 * cos(1.219) + (2.2 + (-2.2)) / 2 ~ 0.759\n";

  EXPECT_NEAR(ksn::sinusoidalmap(10.2, 14.7, 3.1, -2.2, 2.2), -0.759, 0.001)
    << "clamp(10.2, 14.7, 3.1) = 10.2\n"
       "coeff = -(2.2 - (-2.2)) / 2 = -2.2\n"
       "angle = (M_PI * (14.7 - 10.2)) / (14.7 - 3.1) = 1.219\n"
       "-2.2 * cos(1.219) + (-2.2 + 2.2) / 2 ~ -0.759\n";
}

TEST(NumberTest, ClampIntegral)
{
  EXPECT_EQ(ksn::clamp(5, 0, 10), 5) << "0 <= 5 <= 10";
  EXPECT_EQ(ksn::clamp(-5, 0, 10), 0) << "-5 < 0";
  EXPECT_EQ(ksn::clamp(15, 0, 10), 10) << "15 > 10";
}

TEST(NumberTest, ClampFloatingPoint)
{
  EXPECT_DOUBLE_EQ(ksn::clamp(0.5, -3.3, 2.2), 0.5) << "-3.3 <= 0.5 <= 2.2";
  EXPECT_DOUBLE_EQ(ksn::clamp(-5.5, -3.3, 2.2), -3.3) << "-5.5 < -3.3";
  EXPECT_DOUBLE_EQ(ksn::clamp(5.5, -3.3, 2.2), 2.2) << "5.5 > 2.2";
}

TEST(NumberTest, ClampAngle)
{
  EXPECT_EQ(ksn::clamp(0_deg, -90_deg, 45_deg), 0_deg) << "-90 <= 0 <= 45";
  EXPECT_EQ(ksn::clamp(-180_deg, -90_deg, 45_deg), -90_deg) << "-180 < -90";
  EXPECT_EQ(ksn::clamp(90_deg, -90_deg, 45_deg), 45_deg) << "90 > 45";
}

TEST(NumberTest, WrapIntegral)
{
  EXPECT_EQ(ksn::wrap(13, 10, 15), 13) << "13 - 10 = 3\n"
                                          "15 - 10 = 5\n"
                                          "3 = 5 * 0 + 3\n"
                                          "3 + 10 = 13";

  EXPECT_EQ(ksn::wrap(31, 10, 15), 11) << "31 - 10 = 21\n"
                                          "15 - 10 = 5\n"
                                          "21 = 5 * 4 + 1\n"
                                          "1 + 10 = 11";

  EXPECT_EQ(ksn::wrap(4, 10, 15), 14) << "4 - 10 = -6\n"
                                         "15 - 10 = 5\n"
                                         "-6 = 5 * (-2) + 4\n"
                                         "4 + 10 = 14";
}

TEST(NumberTest, WrapFloatingPoint)
{
  EXPECT_DOUBLE_EQ(ksn::wrap(0.1, -0.1, 0.3), 0.1) << "0.1 - (-0.1) = 0.2\n"
                                                      "0.3 - (-0.1) = 0.4\n"
                                                      "0.2 = 0.4 * 0 + 0.2\n"
                                                      "0.2 + (-0.1) = 0.1";

  EXPECT_DOUBLE_EQ(ksn::wrap(1.8, -0.1, 0.3), 0.2) << "1.8 - (-0.1) = 1.9\n"
                                                      "0.3 - (-0.1) = 0.4\n"
                                                      "1.9 = 0.4 * 4 + 0.3\n"
                                                      "0.3 + (-0.1) = 0.2";

  EXPECT_DOUBLE_EQ(ksn::wrap(0.1, 1.1, 1.5), 1.3) << "0.1 - (1.1) = -1.0\n"
                                                     "1.5 - (1.1) = 0.4\n"
                                                     "-1.0 = 0.4 * (-3) + 0.2\n"
                                                     "0.2 + (1.1) = 1.3";
}

TEST(NumberTest, CurveIntegral)
{
  EXPECT_EQ(ksn::curve(13, 10, 15, 2), 11) << "clamp(13, 10, 15) = 13\n"
                                              "10 + (15 - 10) * ((13 - 10) / (15-10))^2 = 11";

  EXPECT_EQ(ksn::curve(31, 10, 15, 2), 15) << "clamp(31, 10, 15) = 15\n"
                                              "10 + (15 - 10) * ((15 - 10) / (15-10))^2 = 15";

  EXPECT_EQ(ksn::curve(4, 10, 15, 2), 10) << "clamp(4, 10, 15) = 10\n"
                                             "10 + (15 - 10) * ((10 - 10) / (15-10))^2 = 10";
}

TEST(NumberTest, CurveFloatingPoint)
{
  EXPECT_EQ(ksn::curve(13.0, 10.0, 15.0, 2.0), 11.8)
    << "clamp(13, 10, 15) = 13\n"
       "10 + (15 - 10) * ((13 - 10) / (15-10))^2 = 11.8";

  EXPECT_EQ(ksn::curve(31.0, 10.0, 15.0, 2.0), 15.0)
    << "clamp(31, 10, 15) = 15\n"
       "10 + (15 - 10) * ((15 - 10) / (15-10))^2 = 15";

  EXPECT_EQ(ksn::curve(4.0, 10.0, 15.0, 2.0), 10.0)
    << "clamp(4, 10, 15) = 10\n"
       "10 + (15 - 10) * ((10 - 10) / (15-10))^2 = 10";
}

TEST(NumberTest, LerpIntegral)
{
  EXPECT_EQ(ksn::lerp(0, 10, 0), 0) << "0 + (10 - 0) * 0 = 0";

  EXPECT_EQ(ksn::lerp(5, 15, 1), 15) << "5 + (15 - 5) * 1 = 15";
}

TEST(NumberTest, LerpFloatingPoint)
{
  EXPECT_DOUBLE_EQ(ksn::lerp(0.0, 10.0, 0.5), 5.0) << "0 + (10 - 0) * 0.5 = 0";

  EXPECT_DOUBLE_EQ(ksn::lerp(5.0, 15.0, 0.25), 7.5) << "5 + (15 - 5) * 0.25 = 15";
}

#define ASSERT_SMOOTH_NEAR(SOURCE, TARGET, RATIO, ...) \
  {                                                    \
    double _source = SOURCE;                           \
    double _values[] = {__VA_ARGS__};                  \
    size_t index = 0;                                  \
    while (_source < (TARGET - (TARGET * RATIO))) {    \
      _source = ksn::smooth(_source, TARGET, RATIO);   \
      ASSERT_NEAR(_source, _values[index++], 0.0001);  \
    }                                                  \
  }

TEST(NumberTest, SmoothValue)
{
  ASSERT_SMOOTH_NEAR(
    0.0, 10.0, 0.1, 1, 1.9, 2.71, 3.439, 4.0951, 4.68559, 5.21703, 5.69533, 6.12579, 6.51322,
    6.86189, 7.1757, 7.45813, 7.71232, 7.94109, 8.14698, 8.33228, 8.49905, 8.64915, 8.78423,
    8.90581, 9.01523);

  ASSERT_SMOOTH_NEAR(
    5.0, 25.0, 0.08, 6.6, 8.072, 9.42624, 10.6721, 11.8184, 12.8729, 13.8431, 14.7356, 15.5568,
    16.3122, 17.0073, 17.6467, 18.2349, 18.7761, 19.2741, 19.7321, 20.1536, 20.5413, 20.898,
    21.2261, 21.528, 21.8058, 22.0613, 22.2964, 22.5127, 22.7117, 22.8948, 23.0632);

  ASSERT_SMOOTH_NEAR(
    8.0, 101.0, 0.08, 15.44, 22.2848, 28.582, 34.3755, 39.7054, 44.609, 49.1203, 53.2706, 57.089,
    60.6019, 63.8337, 66.807, 69.5425, 72.0591, 74.3743, 76.5044, 78.464, 80.2669, 81.9256, 83.4515,
    84.8554, 86.147, 87.3352, 88.4284, 89.4341, 90.3594, 91.2106, 91.9938, 92.7143, 93.3771);
}

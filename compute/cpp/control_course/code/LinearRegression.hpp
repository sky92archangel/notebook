#pragma once

#include "Eigen/Dense"
#include <vector>
// #include <cstddef>

class LinearRegression {

public:
  LinearRegression(std::vector<double>, std::vector<double>);
  ~LinearRegression(){};

private:
  Eigen::Vector<double, 15> vecH;
  Eigen::Matrix<double, 15, 2> matW;
  Eigen::Vector2d result;

public:
  // 显示结果
  void PrintResult();

  // 直接计算
  void Calculate();

  // 梯度下降法
  void GradientCalculte( 
      // Eigen::Vector2d result_guess,
      // Eigen::Matrix<double, 2, 2> alpha,
      int generation_number = 500000) {

    Eigen::Vector2d result_guess;
    Eigen::Matrix<double, 2, 2> alpha;

    alpha << 0.0001, 0.00000, 0.0000, 0.00001;
    result_guess << 100, 2;

    Eigen::Matrix<double, 2, 15> matWT = matW.transpose();

    for (int i = 0; i < generation_number; i++) {
      
      //动态学习率  酌情启用
      //alpha << 0.000001 * result_guess[0], 0.00000, 0.0000, 0.000001 * result_guess[1];

      auto gradient = matWT * (matW * result_guess - vecH);
      result_guess = result_guess - alpha * gradient;
    }
    result = result_guess;
  }
};

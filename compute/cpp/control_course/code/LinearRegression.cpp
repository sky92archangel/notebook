

#include "LinearRegression.hpp"
#include "Eigen/src/Core/Matrix.h"
#include <cmath>

//======================================

LinearRegression::LinearRegression(std::vector<double> hdata,
                                   std::vector<double> wdata) {
  // 数据必须维度相同
  if (hdata.size() != wdata.size()) {
    return;
  }
  // 空参数 则 启用默认数据集
  if (hdata.size() == 0) {
    hdata = {183, 175, 187, 185, 176, 176, 185, 191,
             195, 185, 174, 180, 178, 170, 184};
  }
  // 空参数 则 启用默认数据集
  if (wdata.size() == 0) {
    wdata = {75, 71, 83, 74, 73, 67, 79, 73, 88, 80, 81, 78, 73, 68, 71};
  }
  // SETTING
  for (int i = 0; i < hdata.size(); i++) {
    vecH[i] = hdata[i];
  }
  for (long i = 0; i < wdata.size(); i++) {
    matW(i, 0) = 1;
    matW(i, 1) = wdata[i];
  }
};

void LinearRegression::Calculate() {
  Eigen::Matrix<double, 2, 15> matWT = matW.transpose();
  result = (matWT * matW).inverse() * matWT * vecH;
}

void LinearRegression::PrintResult() {
  printf("\n%f\n", result[0]);
  printf("\n%f\n", result[1]);
 
}
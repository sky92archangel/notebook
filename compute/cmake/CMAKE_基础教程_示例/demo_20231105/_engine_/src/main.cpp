 

#include "core.hpp" 

#include <Eigen/Dense>
#include <iostream>

int main(int argc, char argv[])
{

    Eigen::MatrixXf matrix1(3, 4);         // 定义了矩阵的大小，但是没有初始化。
    matrix1 = Eigen::MatrixXf::Zero(3, 4); // 对矩阵进行初始化。

    Eigen_Sample sample = Eigen_Sample();
    sample.Eigen_Basic();

    int count = 0;
    std::cin >> count;
    return 0;
}

// #include "log.hpp"

#include <core.hpp>

#include <toml++/toml.hpp>
// #include <Eigen/Dense>
#include <Eigen/Dense>
// #include <../../_vendor_/eigen/Eigen/Dense>

#include <iostream>
// using namespace std;

int main()
{
    std::cout << "hello" << std::endl;

    Spdlog_Basic();
    Spdlog_Format();
    Spdlog_Logger();

    MESSAGE("gogoog--+11");
    int minx = MIN(586, 78);
    int maxx = MAX(586, 78);
    MESSAGE(minx);
    MESSAGE(maxx);

    Eigen_Basic();

    Eigen::MatrixXf matrix1(3, 4);         // 定义了矩阵的大小，但是没有初始化。
    matrix1 = Eigen::MatrixXf::Zero(3, 4); // 对矩阵进行初始化。

    MESSAGE(matrix1);
    // std::cout << "------ matrix1 ------" << std::endl << matrix1 << std::endl;

    toml::array tmalArr = toml::array();

    int count = 0;
    std::cin >> count;

    return 0;
}
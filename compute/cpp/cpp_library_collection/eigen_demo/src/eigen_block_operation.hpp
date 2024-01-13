#pragma once

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

void Eigen_Block_Operation()
{

    ArrayXd vec(9);
    vec << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    std::cout << "vec     " << std::endl << vec << std::endl;
    std::cout << "head:   " << std::endl << vec.head(3) << std::endl;
    std::cout << "tail:   " << std::endl << vec.tail(3) << std::endl;
    std::cout << "segment:" << std::endl << vec.segment(3, 3) << std::endl; // 4 5 6


    //-------------------------------------------------------------
    MatrixXd mat(4, 4);
    mat << 
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16;

    std::cout << "mat     " << std::endl << mat << std::endl;
    std::cout << "mat.col:" << std::endl << mat.col(3) << std::endl;
    std::cout << "mat.row:" << std::endl << mat.row(2) << std::endl;
 
    std::cout << "mat.block: " << std::endl << mat.block(1,1,2,2) << std::endl;   //6 7 10 11
    std::cout << "mat.blockx:" << std::endl << mat.block<2,2>(1,1) << std::endl;  //6 7 10 11   num is in <>  location is in ()


}
#pragma once

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

void Eigen_Calculate(){

    Matrix2d mat1;
    mat1<<  4,3,
            2,1 ;
    Matrix2d mat2 ;
    mat2<<  5,6,
            7,8;
    
    std::cout<<"mat1: "<< mat1 << std::endl;
    std::cout<<"mat2: "<< mat2 << std::endl;


    std::cout<<"mat1+mat2: "<< std::endl << mat1 + mat2 << std::endl;
    std::cout<<"mat1-mat2: "<< std::endl << mat1 - mat2 << std::endl;
    std::cout<<"mat1*mat2: "<< std::endl << mat1 * mat2 << std::endl;
    std::cout<<"mat1*0.5: " << std::endl << mat1/2 << std::endl;
   

    std::cout<<"mat1.transpose: " << std::endl << mat1.transpose() << std::endl;
    std::cout<<"mat1.conjugate: " << std::endl << mat1.conjugate() << std::endl;
    std::cout<<"mat1.inverse: " << std::endl << mat1.inverse() << std::endl;    
    std::cout<<"mat1.adjoint: " << std::endl << mat1.adjoint() << std::endl;    //伴随矩阵

    //change mat1 self-data ,such as   mat1=mat1.transposeInPlace()   , "InPlace" can't use in inverse operation;
    mat1.transposeInPlace();
     
}
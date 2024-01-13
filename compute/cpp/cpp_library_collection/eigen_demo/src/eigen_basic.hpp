#pragma once

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
// using namespace Eigen;
 
// template is very useful
template <typename T> using Vec2 = Matrix<T, 1, 2>;
template <typename T> using Mat2 = Matrix<T, 2, 2>;

void Eigen_Basic(){

    //-------------------------------
    Vec2<int> vec;
    vec << 1, 2;
    std::cout << 3 * vec << std::endl;

    //-------------------------------
    Mat2<int> mat2;
    mat2 << 1, 2,
        3, 4;
    std::cout << 4 * mat2 << std::endl;

    //-------------------------------
    Vector2d vec2d;
    vec2d << 1, 2;
    std::cout << vec2d << std::endl;
    vec2d.setZero();
    std::cout <<"vec2d has setZero:"<< vec2d << std::endl;

    //-------------------------------
    MatrixXd mat(2, 2);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            mat(i, j) = 1;
        }
        /* code */
    }
    std::cout << mat << std::endl;

    //-------------------------------
    MatrixXd indentityMatrix = MatrixXd ::Identity(2, 2);
    MatrixXd zeroMatrix = MatrixXd ::Zero(2, 2);
    MatrixXd randomMatrix = MatrixXd ::Random(2, 2);
    MatrixXd onesMatrix = MatrixXd ::Ones(2, 2);

    std::cout 
    << indentityMatrix  << std::endl
    << zeroMatrix       << std::endl
    << randomMatrix     << std::endl
    << onesMatrix       << std::endl
    << std::endl;

    //-------------------------------
    MatrixXd m1(2,2) ;
    m1<< 4,3,2,1 ;
    MatrixXd m2(3,3) ;
    m2<< 1,2,3,4,5,6,7,8,9 ;
   
    //data of m2  will cover m1
    m1=m2 ;
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;
}

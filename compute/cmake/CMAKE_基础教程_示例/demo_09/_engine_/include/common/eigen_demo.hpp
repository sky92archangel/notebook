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
   

    std::cout<<"mat1.transpose: " << std::endl << mat1.transpose() << std::endl;        //转置
    std::cout<<"mat1.conjugate: " << std::endl << mat1.conjugate() << std::endl;        //共轭 复数矩阵常用
    std::cout<<"mat1.inverse: " << std::endl << mat1.inverse() << std::endl;            //逆矩阵
    std::cout<<"mat1.adjoint: " << std::endl << mat1.adjoint() << std::endl;            //伴随矩阵
    std::cout<<"mat1.determinant: " << std::endl << mat1.determinant() << std::endl;    //行列式

    //change mat1 self-data ,such as   mat1=mat1.transposeInPlace()   , "InPlace" can't use in inverse operation;
    mat1.transposeInPlace();
     
}


template <typename T>
using Vec3 = Matrix<T, 1, 3>;

void Eigen_Test()
{

    // MatrixXd m1(3, 3);
    // m1 << 10.0f, 16.0f, 7.0f, 35.0f, 20.0f, 15.0f,100.0f,100.0f,100.0f; // 4,3,2,1 ;
    // Vec3<float> vec;
    // vec << 13.0f, 22.0f,100.0f;
    // VectorXd vec3d;
    // vec3d << 13.0f, 22.0f,100.0f;

    MatrixXd m1(3,3);
     m1 << 
     0,0,1 ,
     1,0,1 ,
     0,1,1  
     ;

     MatrixXd m2(4,4);
     m2 << 
     1,0,0,1 ,
     0,1,0,1 ,
     0,0,1,1 ,
     0,0,0,1  
     ;

    std::cout << m1.determinant() << std::endl;
    std::cout << m2.determinant() << std::endl;
}


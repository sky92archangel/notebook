#pragma once

#define MY_LIB_API __declspec(dllexport) 
 
#include<iostream>
#include<string>
 
inline
void MY_LIB_API myprint(std::string str1, double count);

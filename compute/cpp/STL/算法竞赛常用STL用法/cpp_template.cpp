#include <iostream>
// #include <bits/stdc++.h>  

template<typename T>
void printValue(const T& value) {
    std::cout << "The value is: " << value << std::endl;
}

template<typename T>
void DoubleValue(const T& value ) {
    std::cout << "The value is: " << value *2 << std::endl;
}

int main() {
    printValue(5);       // 打印整数值
    printValue(3.14);   // 打印浮点数值

	DoubleValue(5.24f);
	DoubleValue(5.24d);
	DoubleValue(5);
    return 0;
}
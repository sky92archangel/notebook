#include <iostream>
#include <vector>
 
// 定义一个简单的宏来构建一个向量
#define BUILD_VECTOR(type, ...) \
    std::vector<type> {__VA_ARGS__}
 
int main() {
    // 使用宏构建一个整数向量
    std::vector<int> myVector = BUILD_VECTOR(int, 1, 2, 3, 4, 5);
 
    // 打印向量中的元素
    for (int num : myVector) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
 
    return 0;
}
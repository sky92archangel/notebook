#include <iostream>
#include <vector>
// #include <ranges>

#include <bits/stdc++.h>



int main() {
    // 创建一个整数向量
    std::vector<int> nums{1, 2, 3, 4};

    // 使用std::ranges::filter筛选出所有奇数
    auto filtered_nums = std::ranges::filter(nums, [](int n) { return n % 2 == 1; });

    // 输出筛选后的结果
    for (int n : filtered_nums) {
        std::cout << n << ' ';
    }
    std::cout << std::endl;

    return 0;
}
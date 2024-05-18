#include <iostream>
#include <vector>

#include <bits/stdc++.h> 
 
// 定义一个简单的宏来构建一个向量
#define BUILD_VECTOR(type, ...) \
    std::vector<type> {__VA_ARGS__}
    
#define PRINT(str) std::cout<<str<<std::endl;

#define PRINT_VECTOR(vec) \
	for(auto & v :vec){std::cout<<v<<std::endl;	}
 
using namespace std;
 

class Solution{
public:
    	vector<int> grayCode(int n)
		{
        vector<int> gray;
        if (n < 1) {
            gray.push_back(0);
            return gray;
        }
        int num = pow(2,n);
        int graycode[n];
        for (int i = 0; i < num; i++) 
		{
            IntToBit(graycode, i, n);
            BitToGray(graycode,n);
            gray.push_back(GrayBitToInt(graycode, n));
        }
        return gray;
    }
    
    void IntToBit(int *code, int n, int bit){
        int i = bit-1;
        while (i >= 0) {
            code[i--] = n%2;
            n/=2;
        }
    }
    
    void BitToGray(int *code, int bit){
        int temp[bit];
        temp[0] = 0^code[0];
        for (int i = 0; i < bit-1; i++) {
            temp[i+1] = code[i]^code[i+1];
        }
        for (int i = 0; i < bit; i++) {
            code[i] = temp[i];
        }
    }
    
    int GrayBitToInt(int *code, int bit){
        int number = 0;
        for (int i = 0; i < bit; i++) {
            if (code[i] == 1) {
                number += pow(2, bit-i-1);
            }
        }
        return number;
    }
    
};
 

int main() {
    
  	vector<int> test;
    Solution sl;
    test = sl.grayCode(3);
    vector<int>::iterator iter;
    for (iter = test.begin(); iter != test.end(); iter++) {
        printf("%d\n",*iter);
 
    
    return 0;
}


















#include <bits/stdc++.h>  

#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl ;

#define PRINT_VECTOR(arrx) 			\
std::cout<<"==========="<<std::endl;\
for(auto & ele:arrx) {				\
		std::cout<<ele<<std::endl;  \
	} 

using namespace std;
   
int gcd(int a, int b ){
   	if(!b)return a;
   	return gcd(b,a%b);
   }
int lcm(int a, int b ){
   	return a/gcd(a,b)*b;
   }   
    
int main()
{   
	
	/*sort reserve sort unique swap */
  
	PRINT(abs(-1.0));
	PRINT(exp(2));
	PRINT(log(2.7321));
	PRINT(pow(2,3));
	PRINT(sqrt(16))
	PRINT(ceil(2.1))
	PRINT(floor(3.2))
	PRINT(round(2.1))
	PRINT(round(2.8))
    
 
//最大公因数
  	PRINT(__gcd(8,12))	//g++专用
//最小公倍数
	PRINT(__lcm(8,12))
 
	return 0;
 
} 
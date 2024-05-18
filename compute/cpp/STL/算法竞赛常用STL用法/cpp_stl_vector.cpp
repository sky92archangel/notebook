#include <bits/stdc++.h>
#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl;
#define PRINT_VECTOR(arrx) 			\
std::cout<<"==========="<<std::endl;\
for(auto & ele:arrx) {				\
		std::cout<<ele<<std::endl;  \
	} 								\
 
using namespace std;

int main(){ 

//define
	vector<float>arrx(5,1);
	for(auto & ele:arrx)
	{
		PRINT(ele)  
	}
	PRINT(arrx.empty())
	PRINT(arrx.size())

//matrix  form vector 
	vector<vector<int>> mat2 (3,vector<int>(3)); 
	vector<vector<vector<int>>> mat3 
			(2,vector<vector<int>>(2,vector<int>(3))); 
	map<tuple<int,int>,float> matrixt2d ;
	map<pair<int,int>,float> matrixp2d ;
 
//push
	vector<int> arr;
	arr.push_back(3);
	arr.push_back(56);
	arr.push_back(34);
	PRINT_VECTOR(arr) 

	arr.resize(5); 
	PRINT_VECTOR(arr) 

	arr.pop_back();
	PRINT_VECTOR(arr) 

	arr.push_back(99);
	PRINT(arr.back())
	PRINT(arr.front()) 
	
	return 0;
}
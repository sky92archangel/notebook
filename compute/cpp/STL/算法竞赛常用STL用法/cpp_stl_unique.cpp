#include <bits/stdc++.h>  

#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl ;

#define PRINT_VECTOR(arrx) 			\
std::cout<<"==========="<<std::endl;\
for(auto & ele:arrx) {				\
		std::cout<<ele<<std::endl;  \
	} 

using namespace std;
   
int main()
{   
	
	/*sort reserve sort unique swap */
 
 
 //C++11
 
	vector<int> vec = {0,88,4,4,4,7,8,14,55}; 
	 
	sort(vec.begin(),vec.end());
	auto endIter=unique(vec.begin(),vec.end());
	PRINT_VECTOR(vec)
	vec.erase(endIter,vec.end());
	PRINT_VECTOR(vec)
  	
 
	return 0;
 
} 
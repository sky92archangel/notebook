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
 
 
  	vector<int> vec = {0,1,4,4,4,7,8,14,55}; 
	 
	reverse(vec.begin(),vec.end());
 
	PRINT_VECTOR(vec) 
 
	reverse(vec.begin()+1,vec.end()-2);
	
	PRINT_VECTOR(vec) 
 
	return 0;
 
} 
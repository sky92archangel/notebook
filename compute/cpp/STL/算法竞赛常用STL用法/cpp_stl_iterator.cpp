#include <bits/stdc++.h>  

#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl ;
   
using namespace std;
  
int main()
{   
	 vector<int> vec = {4,4,78,1,5};
	 for(int i = 0 ; i < vec.size();i++){
	 	PRINT(vec[i])
	 }

	for(vector<int>::iterator it = vec.begin();it!=vec.end();++it){
		PRINT(*it)
	}
  
} 
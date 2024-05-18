#include <bits/stdc++.h>  

#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl ;
    
using namespace std;
   
int main()
{   
	
	/*sort reserve sort unique swap */
 \
 //二分查找   务必先排序
  	vector<int> vec = {0,1,4,4,4,7,8,14,55}; 

	int pos =lower_bound(vec.begin(),vec.end(),33)-vec.begin();
	PRINT(pos)

	    pos =upper_bound(vec.begin(),vec.end(),33)-vec.begin();
	PRINT(pos)

	return 0;
 
} 
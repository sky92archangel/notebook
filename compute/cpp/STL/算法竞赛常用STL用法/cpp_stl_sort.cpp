#include <bits/stdc++.h>  

#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl ;
   
#define PRINT_VECTOR(arrx) 			\
std::cout<<"==========="<<std::endl;\
for(auto & ele:arrx) {				\
		std::cout<<ele<<std::endl;  \
	} 
	
using namespace std;
  
  ///比较器
bool cmp(pair<int,int>a ,pair<int,int> b){
	//second min->max
	if(a.second!=b.second) return a.second<b.second;
	else{
		//first max->min
		return a.first>b.first;
	}
}
 
int main()
{   
	
	/*sort reverse sort unique swap */
  
//sort
	vector<int> vec = {4,4,78,1,5};
	sort(vec.begin(),vec.end(),greater<int>());
	PRINT_VECTOR(vec)
	
	vector<pair<int,int>> arr = {{4,4},{4,8},{7,8},{7,1},{5,9}};
	sort(arr.begin(),arr.end(),cmp);
	for(auto  & ar : arr){
		cout<<ar.first<<":"<<ar.second<<endl;
	}
    
} 
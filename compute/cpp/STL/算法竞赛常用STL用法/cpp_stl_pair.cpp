#include <bits/stdc++.h>  

#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl ;
   
using namespace std;
  
int main()
{   
	//C++98
	pair<int,int> p1 = make_pair(1,2);
	
	//C++11
	pair<int,int> p2= {1,2};
	PRINT( p2.first )
	PRINT(p2.second)
	if(p1==p2){PRINT("yes") }

	tuple<int,int,double> tp (3,5,78.2);
	PRINT(get<0>(tp))
	 
} 
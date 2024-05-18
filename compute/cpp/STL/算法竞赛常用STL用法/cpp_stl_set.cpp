#include <bits/stdc++.h> 
#include<string>

#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl;
  
#define PRINT_SET(st) 						\
	std::cout<<"========="<<std::endl;		\
	for(auto & ele :st){ cout<<ele<<endl; }	\

using namespace std;
  
int main()
{ 
PRINT("顺序集合") ;
 	set<int> st1 ; 
	st1.insert(1);
	st1.insert(0);
	st1.insert(3);
	st1.insert(9);
	st1.insert(9);
	PRINT(st1.size()) 
	PRINT(*st1.end());
PRINT("earse:")
	st1.erase(0);
	PRINT(st1.size())
	PRINT_SET(st1)  
PRINT("find:")
	if(st1.find(3) != st1.end())
	{PRINT("YES")} 
	PRINT(st1.count(9))
PRINT("distance:")
	PRINT(distance(st1.begin(),st1.find(9)))
PRINT("iter:")
	//老旧的迭代器
	for	(set<int>::iterator it = st1.begin();it!=st1.end();++it){
		cout<<"::"<< *it<<endl;
	}
PRINT("clear:")
	st1.clear();
	PRINT(st1.empty())

PRINT("逆序集合") ;
 	set<int,greater<int>> st2 ;
	st2.insert(1);
	st2.insert(0);
	st2.insert(3);
	st2.insert(3);
	PRINT_SET(st2)


 

PRINT("无序集合") ;
 	unordered_set<int> ust ;
	ust.insert(1);
	ust.insert(6);
	ust.insert(4);
	ust.insert(4);
	PRINT_SET(ust)


PRINT("可重集合") ;
  	multiset<int> mset ;
	mset.insert(1);
	mset.insert(6);
	mset.insert(4);
	mset.insert(4);
	PRINT_SET(mset)


  	
  
}

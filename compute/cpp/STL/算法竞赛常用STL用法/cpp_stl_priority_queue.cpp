#include <bits/stdc++.h> 

#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl;

using namespace std;
  
int main()
{ 
PRINT("大顶堆")
	//int 大顶堆
	priority_queue<int > pque1 ;
 
  	pque1.push(3); 
  	
	// PRINT(pque1.size())
	PRINT(pque1.top())
	
	pque1.push(6);
	PRINT(pque1.top())

	pque1.push(4);
	PRINT(pque1.top())

	pque1.pop();
	PRINT(pque1.top())

PRINT("小顶堆")
	//int 小顶堆
	priority_queue<int,vector<int>,greater<int> > pque2 ;
 
 	pque2.push(3); 
  	
	// PRINT(pque2.size())
	PRINT(pque2.top())
	
	pque2.push(6);
	PRINT(pque2.top())

	pque2.push(4);
	PRINT(pque2.top())

	pque2.pop();
	PRINT(pque2.top())

 
  
}

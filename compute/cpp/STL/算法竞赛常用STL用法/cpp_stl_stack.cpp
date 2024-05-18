#include <bits/stdc++.h> 
#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl;

using namespace std;
 
  
int main()
{ 
  	stack<double> stk ;
  	stk.push(0.94);
  	stk.push(0.54);
  	stk.push(2.54);
  	stk.push(4.55);
	PRINT(stk.top()) 
	
	stk.pop();
	PRINT(stk.top())

	PRINT(stk.empty())
	 
	PRINT(stk.size())
 
}

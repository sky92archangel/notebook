#include <bits/stdc++.h> 
#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl;

using namespace std;
  
int main()
{ 
  	queue<double> queue ;
  	queue.push(0.94);
  	queue.push(0.54);
  	queue.push(2.54);
  	queue.push(4.55);  
	PRINT(queue.front())
	PRINT(queue.back())
	 
	queue.pop();
	PRINT(queue.front())
	PRINT(queue.back())
	 
	PRINT(queue.empty())
	 
	PRINT(queue.size())
  
}


#include <bits/stdc++.h>  
#include <iostream>
#include <functional>
// #include <vector>
#include <time.h>

#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl;
  
using namespace std;
    
//===========================   
clock_t start,stop;
double duration;
   
int main() {
   
   	start=clock();
   
   	
   
	stop=clock(); 
	duration=((double)(stop-start ) )/CLK_TCK; 
	PRINT(duration);
    return 0;
}
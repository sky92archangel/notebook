#include <bits/stdc++.h>  

#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl 
   
using namespace std;
  
int main()
{   
	string s ;
	cin>>s;
	cout<<s;	
	 
	 string ss(10,'7');
	 PRINT(ss) ;	
	 
	 ss[8]='4';
	 PRINT(ss) ;
	 
	 
	 string  s1 = "123";
	 string  s2 = "129";
	 s1==s2 ?  PRINT("yes") : PRINT("no") ;
	 
	 PRINT(s1+s2);
	 
	 PRINT( ss.substr(3,2));
	 
	 //find为暴力查找
	 if(ss.find("747")!=string::npos){
	 	PRINT("YES");
	 }
	 
	 
	long double xx= stold("145.25487");
	 PRINT(xx);
	 
	 string sss =to_string( xx);
	  PRINT(sss);
	 
} 
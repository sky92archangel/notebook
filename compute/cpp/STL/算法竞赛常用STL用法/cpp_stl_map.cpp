#include <bits/stdc++.h>  

#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl;
  
#define PRINT_MAP(mapx) \
	for(auto & pr:mapx){ cout<< pr.first <<':'<<pr.second<<endl;}
  
using namespace std;
  
int main()
{  
//顺序map
  	map<string,float> mp ;
  	mp["cvse"] = 4.3;
	mp["c3cf"] = 8.12;
	PRINT_MAP(mp);
	PRINT(mp["cvse"])
 
	if(mp.find("cvse")!=mp.end())
	 { PRINT("yes") } 
	else{ PRINT("NO") }
	
	mp.erase("c3cf");
	
	/* size empty size count */

//逆序map
	map<int,float,greater<int>> mapp ;
	

	//旧迭代器
	for(map<string,float>::iterator it = mp.begin();it!=mp.end();++it){
		cout<< it->first <<':'<<it->second<<endl;
	}
	//C++11新循环器
	for(auto  & pr:mp){
		cout<< pr.first <<':'<<pr.second<<endl;
	}
	//C++17循环
	for(auto & [key,val]:mp){
		cout<< key <<':'<<val<<endl;
	}
	
}

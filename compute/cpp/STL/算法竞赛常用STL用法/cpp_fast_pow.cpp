#include<iostream>
#include <bits/stdc++.h>  

using namespace std;
long long fpow(long long a,long long b){
	long long ans=1;
	while(b){
		if(b&1)ans*=a;
		b>>=1;
		a*=a;
	} 
	return ans;
}
int main(){

	long long n,m;
	cin>>n>>m;
	
	 cout<<fpow(n,m)<<endl;
	 cout<< pow(n,m)<<endl;	
}

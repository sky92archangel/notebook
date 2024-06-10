#include <functional>
#include <bits/stdc++.h>  
#include <iostream>
// #include <vector>

#define PRINT(s)  std::cout<<"========="<<std::endl<<s<<std::endl;


using namespace std;
 
// 定义一个函数类型
typedef std::function<void(int)> IntEvent;
 
class EventSource {
private:
    std::vector<IntEvent> onIntEvent;
 
public:

	//增加委托方法
    void AddListener(const IntEvent& listener) {
        onIntEvent.push_back(listener) ;
    }
 	
 	//移除委托方法
    void RemoveListener(const IntEvent& listener) { 
    	//不含有直接返回
	    if(!ContainListener(listener)) { return ;}
	    //获得需要删除的函数位置
         auto indexs = IndexListener(listener);
         for(int index : indexs){
         	 onIntEvent[index] = [](int){}  ;
         } 
    } 

	//包含  contain listener
    bool ContainListener(const IntEvent& listener){
    	return IndexListener(listener).size() > 0 ; 
    }
    //获得所有匹配函数的对应的位置
    vector<int> IndexListener(const IntEvent& listener){
		vector<int> indexs;
    	for(int i= 0 ; i < (int)onIntEvent.size();i++ ){
    		 if(GetAddress(&onIntEvent[i]) == GetAddress(&listener)) 
    		 {
    		 	indexs.push_back ( i );
    		 }
 			if(GetAddress(&onIntEvent[i]) == GetAddress(&listener)) 
    		 {
    		 	indexs.push_back ( i );
    		 }
    		
    	}
    	return indexs;
    }
    
 	//运行多播委托
    void Trigger(int value) {
    	for(auto & func : onIntEvent){
    		func(value);
    	} 
    }
    
    inline
    std::string GetAddress(const void* ptr) {
	    std::stringstream ss;
	    ss << ptr;
	    return ss.str();
	}
 
};
 
void ListenerFunction(int value) {
    std::cout << "Value: " << value << std::endl;
}

void ListenerFunction2(int value) {
    std::cout << "Value: " << value+2 << std::endl;
}
 
int main() {
    EventSource eventSource;
    eventSource.AddListener(ListenerFunction);
  	eventSource.AddListener(ListenerFunction2);
	PRINT(__func__);
  	eventSource.RemoveListener(ListenerFunction2);
    eventSource.Trigger(42); // 输出: Value: 42
    return 0;
}
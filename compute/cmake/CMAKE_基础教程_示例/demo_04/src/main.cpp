#include <iostream>
#include <stdlib.h>
#include "mymath.hpp"
// #include "../mylib/mymath.hpp"
using namespace std;

// double power(double base , double exp)
// {
//     int res = base;
//     if(base ==1)
//     {
//         return 1;
//     }
//     for (int i = 1; i < exp; i++)
//     {
//         res = res*base;
//     }
//     return res;
// }
 
int main(int argc , char *argv[])
{ 
    if(argc<3)
    {
        cout<<"Usage:"<<argv[0]<<endl;
        return 1; 
    }
    double base = atof(argv[1]);
    int exp=atoi(argv[2]);
    cout<<"result:"<<endl<<power(base,exp);
    return 0;
}
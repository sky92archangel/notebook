#include <iostream>
#include <stdlib.h>
#include "mymath.hpp"
#include "myprint.hpp"
// #include "../mylib/mymath.hpp"
// using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage:" << argv[0] << std::endl;
        return 1;
    }
    double base = atof(argv[1]);
    int exp = atoi(argv[2]);
    std::cout << "result:" << std::endl
              << power(base, exp);

    myprint("result is ", power(base, exp));
#if DEBUG
    std::cout << " DEBUG ON " << std::endl;
#endif
    return 0;
}
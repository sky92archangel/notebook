

#include "cgmath.hpp"
#include <assert.h>

// using namespace Microsoft::VisualStudio::CppUnitTestFramework;

int main(int argc, char **argv)
{
    Cgmath Cgmath = Cgmath::Cgmath();
    double res = Cgmath.Squre2(2,4);

    assert(res<2);

    return 0;
}

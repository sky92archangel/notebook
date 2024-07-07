

#include "LinearRegression.hpp"
#include <vector>

void Excute() {

  std::vector<double> a{};
  std::vector<double> b{};

  // LinearRegression *linRgs = new LinearRegression(a, b);
  // linRgs->Calculate();
  // linRgs->PrintResult();

  LinearRegression linRgs(a, b);
  linRgs.Calculate();
  linRgs.PrintResult();
  linRgs.GradientCalculte();
  linRgs.PrintResult();
}

int main() {
  Excute();
  return 0;
}
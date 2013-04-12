#include <iostream>
#include "GammaLib.hpp"
int main(void) {
  std::cout << gammalib::gammln(42) << std::endl;
  std::cout << gammalib::li_ma_significance(10, 20, 0.1) << std::endl;
  return 0;
}

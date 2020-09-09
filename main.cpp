#include <iostream>
#include "functions.hpp"

int main() {
  double x1, x2, x3, x4;
  double p2, p3;
  double c1, c2, c3;

  std::cout << "--------------- 1 PART ---------------\n";
  double x = 0.1;
  do {
      x1 = x;
      x3 = 4 - x1;

      calculateC1(c1, x1, x3);
      calculateC2(c2, x1, x3);
      calculateC3(c3, x1, x3);

      calculateP3(p3, c1, c2, c3);
      calculateP2(p2, p3, x1, x3);
      std::cout << "p3: " << p3 << "\n";
      std::cout << "p2: " << p2 << "\n";
      std::cout << '\n';

      calculateX2(x2, p2, p3, x1);
      calculateX4(x4, p3, x1, x2);

      x += 0.1;
  } while (x < 2);

  std::cout << "--------------- 2 PART ---------------\n";
  std::cout << "--- p3 in [0.1, 1.0] with  h = 0.1 ---\n";
  getP2P3(p2, p3, 0.1, 1.0);

  std::cout << "--- p3 in [1, 10] with  h = 1 ---\n";
  getP2P3(p2, p3, 1, 10);

  std::cout << "--- p3 in [10, 100] with  h = 10 ---\n";
  getP2P3(p2, p3, 10, 100);

  std::cout << "---- p3 in [100, 1000] with h = 100 ---\n";
  getP2P3(p2, p3, 100, 1000);

  std::cout << "-THE VALIDATION BLOCK [control point]-\n";
  x1 = 1; 
  x3 = 4 - x1;

  calculateC1(c1, x1, x3);
  calculateC2(c2, x1, x3);
  calculateC3(c3, x1, x3);

  calculateP3(p3, c1, c2, c3);
  calculateP2(p2, p3, x1, x3);

  calculateX2(x2, p2, p3, x1);
  calculateX4(x4, p3, x1, x2);

  firstCheck(p2, p3, x1, x2, x3, x4);
  secondAndThirdCheck(p2, p3, x1, x2, x3, x4);

  return 0;
}

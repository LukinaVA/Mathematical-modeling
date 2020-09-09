#include <cmath>
#include <iostream>

#include "cmath.h"
#include "functions.hpp"

void calculateC1(double &c1, double &x1, double &x3) {
  c1 = - 400 * x1 * pow(x3, 3) - 400 * pow(x1, 3) * x3 + 3200 * x1 * pow(x3, 2) - 6400 * pow(x3, 2)
       - 200 * pow(x1, 4) - 400 * pow(x1, 2) * pow(x3, 2) - 200 * pow(x3, 4) + 1600 * pow(x1, 2) * x3
       + 1600 * pow(x3, 3);
};

void calculateC2(double &c2, double &x1, double &x3) {
  c2 = - 200 * pow(x1, 3) * x3 - 200 * x1 * pow(x3, 3) + 1600 * x1 * pow(x3, 2) - 3200 * pow(x3, 2)
       - 40 * pow(x1, 3) * pow(x3, 3) + 60 * pow(x1, 4) * pow(x3, 2) - 160 * pow(x1, 3) * pow(x3, 2)
       - 200 * pow(x1, 2) * pow(x3, 2) - 100 * pow(x3, 4) - 20 * pow(x1, 2) * pow(x3, 4)
       - 100 * pow(x1, 4) + 800 * pow(x1, 2) * x3 + 800 * pow(x3, 3) + 160 * pow(x1, 2) * pow(x3, 3);
};

void calculateC3(double &c3, double &x1, double &x3) {
  c3 = - 20 * pow(x1, 3) * pow(x3, 3) + 30 * pow(x1, 4) * pow(x3, 2) - 80 * pow(x1, 3) * pow(x3, 2)
       - 10 * pow(x1, 2) * pow(x3, 4) + 80 * pow(x1, 2) * pow(x3, 3);
};

void calculateP2(double &p2, double p3, double x1, double x3) {
  p2 = x3 / (2 * x1) + x1 / (2 * x3) + ( x1 * x3) / 10 + (x1 * p3) / x3
       + (x3 * p3) / x1 + (x1 * x3) / (20 * p3);

};

void calculateP3(double &p3, double c1, double c2, double c3) {
  double d =  pow(c2, 2) - 4 * c1 * c3;
  double p3_1 = (-c2 + sqrt(d)) / (2 * c1);
  double p3_2 = (-c2 - sqrt(d)) / (2 * c1);

  //p3 > 0
  p3 = p3_1 > 0 ? p3_1 : p3_2;

};

//(***)
void calculateX2(double &x2, double p2, double p3, double x1) {
  x2 = (p2 * x1 + (1 +2 * p3) * (x1 - 2)) / (x1 * x1);
};

//(**)
void calculateX4(double &x4, double p3, double x1, double x2) {
  x4 = ((1 + 2 * p3) * (x1 - 2) + 10 * p3 * x2) / (10 * p3);
};

void getP2P3(double &p2, double &p3, double start, double end) {
  p3 = start;
  while (p3 <= end) {
    p2 = 2 * p3 + 1.4 + 0.2 * (1 / p3);
    std::cout << "p3: " << p3 << "\n";
    std::cout << "p2: " << p2 << "\n";
    std::cout << '\n';
    p3 += start;
  }
  std::cout << '\n';
};

void firstCheck(double p2, double p3, double x1, double x2, double x3, double x4) {
  //1 PART
  double dx[4];
  dx[0] = 2 - (p2 + 1) * x1 + pow(x1, 2) * x2 + p3 * (x3 - x1);
  dx[1] = p2 * x1 - pow(x1, 2) * x2 + 10 * p3 * (x4 - x2);
  dx[2] = 2 - (p2 + 1) * x3 + pow(x3, 2) * x4 - p3 * (x3 - x1);
  dx[3] = p2 * x3 - pow(x3, 2) * x4 - 10 * p3 * (x4 - x2);

  bool successfully = true;
  for (int i = 0; i < 4; ++i) {
    if (dx[i] > 1e-15) {
      successfully = false;
      break;
    }
  }

  if (!successfully) {
    std::cout << "1 CHECK FAILED\n";
  } else {
    std::cout << "1 CHECK PASSED\n";
  }
};

void secondAndThirdCheck(double p2, double p3, double x1, double x2, double x3, double x4) {
  //2 PART
  int n = 4;
  int nm = 4;
  double wr[n], wi[n];
  int ierr;

  double detY[n][n] = {
    {-p2 -1 + 2 * x1 * x2 - p3, pow(x1, 2), p3, 0},
    {p2 - 2 * x1 * x2, -pow(x1, 2) - 10 * p3, 0, 10 * p3},
    {p3, 0, -p2 - 1 + 2 * x3 * x4 - p3, pow(x3, 2)},
    {0, 10 * p3, p2 - 2 * x3 * x4, -pow(x3, 2) - 10 * p3}
  };

  double matrix[n * n];
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      matrix[4 * i + j] = detY[i][j];
    }
  }

  qr(n, nm, matrix, wr, wi, &ierr);

  bool successfully = false;
  for (int i = 0; i < n; ++i) {
    if (wr[i] < 1e-15) {
      successfully = true;
      break;
    }
  }

  if (!successfully) {
    std::cout << "2 CHECK FAILED\n";
  } else {
    std::cout << "2 CHECK PASSED\n";
  }

  //3 PART
  //p2
  std::cout << "3 CHECK: \n";

  detY[0][0] = -x1;
  detY[1][0] = x1;
  detY[2][0] = -x3;
  detY[3][0] = x3;

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      matrix[4 * i + j] = detY[i][j];
    }
  }

  qr(n, nm, matrix, wr, wi, &ierr);

  for (int i = 0; i < n; ++i) {
    std::cout << "wr: " << wr[i] << " wi: " << wi[i] << '\n';
  }
  std::cout << '\n';

  //p3
  detY[0][0] = x3 - x1;
  detY[1][0] = 10 * (x4 - x2);
  detY[2][0] = x1 - x3;
  detY[3][0] = -10 * (x4 - x2);

  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      matrix[4 * i + j] = detY[i][j];
    }
  }

  qr(n, nm, matrix, wr, wi, &ierr);

  for (int i = 0; i < n; ++i) {
    std::cout << "wr: " << wr[i] << " wi: " << wi[i] << '\n';
  }
  std::cout << '\n';
};

#include <iostream>
#include <cmath>
#include <iomanip>
#include <complex>
#include <vector>
#include <functional>
#include "libtap-master/tap.h"

using namespace std;

typedef complex<long double> ComplexNumber;

//Ferrari formula for fining roots
vector<ComplexNumber> GetRoots( long double a,  long double b,  long double c,  long double d,  long double e) {
  vector<ComplexNumber> x(4);
  ComplexNumber alfa = -3.L * pow(b, 2.L) / (8.L * pow(a, 2.L)) + c / a;
  ComplexNumber betta = pow(b, 3.L) / (8.L * pow(a, 3.L)) - b * c / (2.L * pow(a, 2.L)) + d / a;
  ComplexNumber gamma = -3.L * pow(b, 4.L) / (256.L * pow(a, 4.L)) +
                        pow(b, 2.L) * c / (16.L * pow(a, 3.L)) - b * d / (4.L * pow(a, 2.L)) + e / a;
  if(abs(betta) < pow(10.L,-9.L)){
    x[0] = -b/(4.L*a)+sqrt((-alfa+sqrt(pow(alfa,2.L)-4.L*gamma))/2.L);
    x[1] = -b/(4.L*a)+sqrt((-alfa-sqrt(pow(alfa,2.L)-4.L*gamma))/2.L);
    x[2] = -b/(4.L*a)-sqrt((-alfa+sqrt(pow(alfa,2.L)-4.L*gamma))/2.L);
    x[3] = -b/(4.L*a)-sqrt((-alfa-sqrt(pow(alfa,2.L)-4.L*gamma))/2.L);
  } else {
    ComplexNumber P = -pow(alfa, 2.L) / 12.L - gamma;
    ComplexNumber Q = -pow(alfa, 3.L) / 108.L + alfa * gamma / 3.L - pow(betta, 2.L) / 8.L;
    ComplexNumber R = -Q / 2.L + pow(pow(Q, 2.L) / 4.L + pow(P, 3.L) / 27.L, 0.5L);
    ComplexNumber U = pow(R, 1.L / 3.L);
    ComplexNumber y = -5.L * alfa / 6.L + U;
    if (abs(U) < pow(10.L, -9.L)) {
      y += pow(Q, 1.L / 3.L);
    } else {
      y += -P / (3.L * U);
    }
    ComplexNumber W = pow(alfa + 2.L * y, 0.5L);

    x[0] = (-b / (4.L * a) + (W - pow(-(3.L * alfa + 2.L * y + 2.L * betta / W), 1.L / 2.L)) / 2.L);
    x[1] = (-b / (4.L * a) + (W + pow(-(3.L * alfa + 2.L * y + 2.L * betta / W), 1.L / 2.L)) / 2.L);
    x[2] = (-b / (4.L * a) + (-W - pow(-(3.L * alfa + 2.L * y - 2.L * betta / W), 1.L / 2.L)) / 2.L);
    x[3] = (-b / (4.L * a) + (-W + pow(-(3.L * alfa + 2.L * y - 2.L * betta / W), 1.L / 2.L)) / 2.L);
  }
  return x;
}


long double SolveIntegral( long double a4,  long double a3,  long double a2,  long double a1,  long double a0) {
  ComplexNumber ans = 0.L;
  vector<ComplexNumber> omega = GetRoots(a4,a3,a2,a1,a0);

  ComplexNumber i(0.L,1.L);
  ComplexNumber a = omega[0];
  ComplexNumber b = omega[1];
  ComplexNumber c = omega[2];
  ComplexNumber d = omega[3];
  // analitic formula for integral
  ans =  3.14159265358979323846264338327950288419716939937510582097L * i *(
    + (a.imag() >= 0.0L ? 1.L : -1.L) /((a - b) * (a - c) * (a - d))
    + (b.imag() >= 0.0L ? 1.L : -1.L) /((b - a) * (b - c) * (b - d))
    + (c.imag() >= 0.0L ? 1.L : -1.L) /((c - a) * (c - b) * (c - d))
    + (d.imag() >= 0.0L ? 1.L : -1.L) /((d - a) * (d - b) * (d - c))
  );
  ans = abs(ans)/a4;
  return ans.real();
}

void test() {
  long double accuracy = pow(10,-9);
  plan(5);
  ok(abs(SolveIntegral(1, 0, 0, 0, 16) - 0.2776801836L) < accuracy);
  ok(abs(SolveIntegral(1, 0, 1000000, 100099, 999999) - 3.1423994906657376L/1000000.L) < accuracy);
  ok(abs(SolveIntegral(1, 0, 0, 0, 999999) - 0.00007024819999656384712594L) < accuracy);
  ok(abs(SolveIntegral(-1, 0, 0, 0, -999999) - (-0.00007024819999656384712594L)) < accuracy);
  ok(abs(SolveIntegral(1, 0, 1600000, 0, 1) - (0.002483645514171064038404671L)) < accuracy);
}


int main() {
  long double a4 = 1, a3 = 0, a2 = 1000000, a1 = 100099, a0 = 999999;
  test();
  cin >> a0 >> a1 >> a2 >> a3 >> a4;
  long double ans = SolveIntegral(a4, a3, a2, a1, a0) ;
  cout << setprecision(15) << ans;
  return 0;
}

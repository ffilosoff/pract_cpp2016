#include <iostream>
#include <cmath>
#include <iomanip>
#include <complex>
#include <vector>
#include <functional>

using namespace std;

typedef complex<long double> ComplexNumber;

ComplexNumber NewToneMethod(long double a, long double b, long double c, long double d, long double e, ComplexNumber x0 = 0, long double accuracy = pow(10,-15)) {
  ComplexNumber xn;
  ComplexNumber f;
  accuracy *= abs(x0);
  f = a * x0 * x0 * x0 * x0 + b * x0 * x0 * x0 + c * x0 * x0 + d * x0 + e;
  xn = x0 - f/( 4.L * a * x0 * x0 * x0 + 3.L * b * x0 * x0 + 2.L * c * x0 + d);
  do {
//    cout << setprecision(10) << x0 << endl;
    x0 = xn;
    f = a * x0 * x0 * x0 * x0 + b * x0 * x0 * x0 + c * x0 * x0 + d * x0 + e;
    xn = x0 - f/( 4.L * a * x0 * x0 * x0 + 3.L * b * x0 * x0 + 2.L * c * x0 + d);
  }while(abs(x0-xn) > accuracy);
  return x0;
}

vector<ComplexNumber> GetRoots( long double a,  long double b,  long double c,  long double d,  long double e) {
  ComplexNumber alfa = -3.L * pow(b, 2.L) / (8.L * pow(a, 2.L)) + c / a;
  ComplexNumber betta = pow(b, 3.L) / (8.L * pow(a, 3.L)) - b * c / (2.L * pow(a, 2.L)) + d / a;
  ComplexNumber gamma = -3.L * pow(b, 4.L) / (256.L * pow(a, 4.L)) +
                        pow(b, 2.L) * c / (16.L * pow(a, 3.L)) - b * d / (4.L * pow(a, 2.L)) + e / a;
  ComplexNumber P = -pow(alfa, 2.L) / 12.L - gamma;
  ComplexNumber Q = -pow(alfa, 3.L) / 108.L + alfa * gamma / 3.L - pow(betta,2.L)/8.L;
  ComplexNumber R = -Q / 2.L + pow(pow(Q, 2.L) / 4.L + pow(P, 3.L) / 27.L, 0.5L);
  ComplexNumber U = pow(R, 1.L / 3.L);
  ComplexNumber y = -5.L * alfa / 6.L + U;
  if (abs(U) < pow(10.L,-9.L)) {
    y += pow(Q,1.L/3.L);
  } else {
    y += -P / (3.L * U);
  }
  ComplexNumber W = pow(alfa + 2.L * y, 0.5L);
  vector<ComplexNumber> x;
  x.push_back(-b / (4.L * a) + (W - pow(-(3.L * alfa + 2.L * y + 2.L * betta / W), 1.L / 2.L)) / 2.L);
  x.push_back(-b / (4.L * a) + (W + pow(-(3.L * alfa + 2.L * y + 2.L * betta / W), 1.L / 2.L)) / 2.L);
  x.push_back(-b / (4.L * a) + (-W - pow(-(3.L * alfa + 2.L * y - 2.L * betta / W), 1.L / 2.L)) / 2.L);
  x.push_back(-b / (4.L * a) + (-W + pow(-(3.L * alfa + 2.L * y - 2.L * betta / W), 1.L / 2.L)) / 2.L);
  x[0] = NewToneMethod(a,b,c,d,e,x[0]);
  x[1] = NewToneMethod(a,b,c,d,e,x[1]);
  x[2] = NewToneMethod(a,b,c,d,e,x[2]);
  x[3] = NewToneMethod(a,b,c,d,e,x[3]);
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
  ans =  3.14159265358979323846264338327950288419716939937510582097L * i *(
    + (a.imag() >= 0.0L ? 1.L : -1.L) /((a - b) * (a - c) * (a - d))
    + (b.imag() >= 0.0L ? 1.L : -1.L) /((b - a) * (b - c) * (b - d))
    + (c.imag() >= 0.0L ? 1.L : -1.L) /((c - a) * (c - b) * (c - d))
    + (d.imag() >= 0.0L ? 1.L : -1.L) /((d - a) * (d - b) * (d - c))
  );
  ans = abs(ans)/a4;
  return ans.real();
}

void PrintTest(bool expr) {
  static long long test_num = 1;
  cout << "Test " << test_num << ": ";
  if(expr) {
    cout << "PASSED";
  } else {
    cout << "Fail";
  }
  cout << endl;
  test_num++;
};

void test() {
  long double accuracy = pow(10,-9);
  PrintTest(abs(SolveIntegral(1, 0, 0, 0, 16) - 0.2776801836L) < accuracy);
  PrintTest(abs(SolveIntegral(1, 0, 1000000, 100099, 999999) - 3.1423994906657376L/1000000.L) < accuracy);
  PrintTest(abs(SolveIntegral(1, 0, 0, 0, 999999) - 0.00007024819999656384712594L) < accuracy);
  PrintTest(abs(SolveIntegral(-1, 0, 0, 0, -999999) - (-0.00007024819999656384712594L)) < accuracy);
}

int main() {
  long double a4 = 1, a3 = 0, a2 = 1000000, a1 = 100099, a0 = 999999;
//  test();
  cin >> a0 >> a1 >> a2 >> a3 >> a4;
  long double ans = SolveIntegral(a4, a3, a2, a1, a0) ;
  cout << setprecision(15) << ans;
//  printf("%.15Lf", ans);
  return 0;
}

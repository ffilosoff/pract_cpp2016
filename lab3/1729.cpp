// MainTest.cpp : Defines the entry point for the console application.
#include <iostream>
#include <math.h>

double ToRad(double aDeg) {
  return aDeg * 3.14159265359 / 360.;
}

double Range(double aR, double aAngle) {
  return 2 * aR * sin(aAngle);
}

int main() {
  double r, a;
  scanf("%lf%lf", &r, &a);
// first, walk to the edge of the island
  double way = r;
// total angle of undiscovered edge
  double angleLeft = 360.0 - 2.0 * a;
// hops count on 2*a "arc" line
  int fullHops = (int) (angleLeft / (2.0 * a));
  way += Range(r, ToRad(2.0 * a)) * fullHops;
// remaining angle to hop
  double angleRemain = angleLeft - fullHops * (2.0 * a);
  way += Range(r, ToRad(angleRemain));
  printf("%.6lf", way);
}


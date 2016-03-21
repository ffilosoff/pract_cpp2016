#include <math.h>
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

void FindRoots(int a, int n) {
  //4 17
  double R = sqrt((double)a);
  bool foundAtLeastOne = false;


  for (int i = 1; i < n; i ++) {
    if((i*i)%n == a) {
      foundAtLeastOne = true;
      cout << i << " ";
    }
  }
  if(!foundAtLeastOne) {
    cout << "No root" << endl;
  } else {
    cout << endl;
  }
}

int main() {
  double k;
  cin >> k;
  int a,n;
  for (int i = 0; i < n; i++) {
    cin >> a >> n;
    FindRoots(a,n);
  }
  return 0;
}

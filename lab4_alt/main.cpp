#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long int llint;

struct xy {
  llint x;
  llint y;
  xy(llint X = 0, llint Y = 0): x(X), y(Y){};
};

class triangle {
  llint a_;
  llint b_;
  llint c_;
  vector<xy> points_();
public:
  triangle(llint a, llint b, llint c) : a_(a), b_(b), c_(c) { }
  bool TryConstruct() {

  }

};


int main() {
  llint a, b, c;
  triangle task(a,b,c);
  return 0;
}
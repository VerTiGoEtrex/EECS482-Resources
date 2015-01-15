#include <iostream>
using namespace std;

int main() {
  int* x = new int;
  double* y = new double;

  int z = *x * *y;

  cout << z << endl;
  return 0;
}

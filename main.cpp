#include "subtype_range_constrained.h"
#include <iostream>
#include <vector>

using namespace std;

void f1(int i) {}
void f2(ct::RangeConstrained<int, 0, 1000> i) {}

int main(void) {

  ct::RangeConstrained<int, 0, 1000> x;
  ct::RangeConstrained<int, 50, 1000> y;
  int z; 
  char c;

  x = 51;
  y = x;
  z = y;
  x = c;
  c = x;

  cout << x << " " << y << " " << z << endl;

  x = 5 + x;
  x = 5 + y;
  x = x + y;
  x = x % y;
  x = x + c;
  x = c + x;

  cout << x << " " << y << " " << z << endl;
  
  cout << ((x > y) | (x < 5)) << endl;
  
  f1(x);
  f2(x);
  f2(y);
  f2(z);
  f2(c);


  cout << x.last() << " " << y.first() << endl;
  
  
  z = -x;
  c = -x;
  x = -x;
  x = -y;
  x = -z;
  x = -c;

  x += 3;
  x += x;
  x += y;
  z += x;
  x += c;
  c += x;

  x++;
  x--;

  ++x;
  --x;

  x = -4;

  return 0;
}



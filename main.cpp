/**
 * @author  Artium Nihamkin <artium@nihamkin.com>
 * @date May 2014 
 *
 * @section LICENSE
 *
 * The MIT License (MIT)
 * Copyright © 2014 Artium Nihamkin, http://nihamkin.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 * 
 * Experimintation and usage examples of the RangeConstrained library.
 *
 */

#include "subtype_range_constrained.h"
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

enum E {
  A,
  B,
  C
};

void f1(int i) {}
void f2(ct::RangeConstrained<int, 0, 1000> i) {}

int main(void) {
  int x;
  ct::RangeConstrained<int, -1000, 1000> c_x1;
  ct::RangeConstrained<int, -20, 20> c_x2;
  
  char c;
  ct::RangeConstrained<char, 'a', 'z'> c_c;

  c = 'a';
  c_c = c;

  c_x1 = c;
  c_x1 = c_c;

  f2(c_c);

  try {
    c_x1 = 20000;
  } catch(out_of_range ex) {
    cout << ex.what()<< endl;
  }

  cout << c_x1 << endl;


  /*
  ct::RangeConstrained<int, 0, 1000> x;
  ct::RangeConstrained<int, 50, 1000> y;
 
  int z; 
  char c = 'Z';

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
  x = -(-x);
  x = -(-y);
  x = -z;
  x = -(-c);

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

  ct::RangeConstrained<E, A, B> e;
  e = A;

  ct::RangeConstrained<char, 50, 200> s;
  s = 3;
  s = (ct::RangeConstrained<char, 50, 200>)x;
  //x = s;
  

  return 0;
  */
}



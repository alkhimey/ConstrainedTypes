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
 * This file contains unit tests of the RangeConstrained library. The unit tests are
 * done with the "catch" library.
 *
 */

#include "subtype_range_constrained.h"
#include <iostream>
#include <vector>
#include <stdexcept>

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

using namespace std;


enum E {
  A, B, C, D, E, F, G
};

typedef ct::RangeConstrained<short, 1, 12> month_t;


TEST_CASE( "basic") {
  ct::RangeConstrained<int, 15, 100> x = 50;
  CHECK_NOTHROW(x = 15);
  CHECK_NOTHROW(x = 100);
  CHECK( x == 100 );

  CHECK_THROWS(x = 14);
  CHECK_THROWS(x = 101);
}




TEST_CASE( "demo", "The demo used in the readme that demonstrates usefullness of this idiom" ) {
  int  revenue[(int)month_t::range_size()];
  
  month_t m;
  while (m < month_t::last()) {
    revenue[m] = 10000;
    m++;
  }

}


TEST_CASE( "enum") {
  ct::RangeConstrained<enum E, B, D> e = C;
  
  CHECK_THROWS(e = E);
  CHECK_THROWS(e = A);
  CHECK(e == C);
  CHECK_NOTHROW(e = D);
  CHECK(e == D);
}


TEST_CASE( "basic addition") {
  ct::RangeConstrained<int, 15, 130> x = 50;
  
  CHECK_NOTHROW(x = x + 15);
  CHECK_NOTHROW(x = x + x);
  CHECK( x == 130 );
  
  CHECK_THROWS(x = x + 1);
  
}

TEST_CASE( "basic substraction") {
  ct::RangeConstrained<int, 0, 100> x = 15;
  
  CHECK_NOTHROW(x = x - 15);
  CHECK_NOTHROW(x = x - x);
  CHECK( x == 0 );
  
  CHECK_THROWS(x = x - 1);
  
}

TEST_CASE( "unary substraction and addition") {
  ct::RangeConstrained<int, 0, 100> x = 99;
  ct::RangeConstrained<int, 0, 100> y = 1;
  
  SECTION( "post" ) {
    CHECK_NOTHROW(x++);
    CHECK_THROWS(x++);
    CHECK( x == 100 );
  
    CHECK_NOTHROW(y--);
    CHECK_THROWS(y--);
    CHECK( y == 0 );
  }

  SECTION( "pre" ) {
    CHECK_NOTHROW(++x);
    CHECK_THROWS(++x);
    CHECK( x == 100 );
    
    CHECK_NOTHROW(--y);
    CHECK_THROWS(--y);
    CHECK( y == 0 );
  }
}

TEST_CASE( "basic comparison") {
  ct::RangeConstrained<int, 0, 100> x = 100;
  ct::RangeConstrained<int, 0, 100> y = 0;
  
  CHECK( x != y);
  CHECK( x > y);
  CHECK( x >= y);
  CHECK( y < x);
  CHECK( y <= x);

  // TODO: Finish
}

TEST_CASE( "attributes") {
  int x = 4;
  ct::RangeConstrained<int, 0, 100> y = 5;

  x = ct::RangeConstrained<int, 0, 100>::first();
  CHECK(x == 0);
  
  x = ct::RangeConstrained<int, 0, 100>::last();
  CHECK(x == 100);
    
  x = ct::RangeConstrained<int, 0, 100>::range_size();
  CHECK(x == 101);

  y = ct::RangeConstrained<int, 0, 100>::first();
  CHECK(y == 0);
    
  y = ct::RangeConstrained<int, 0, 100>::last();
  CHECK(y == 100);

  y = ct::RangeConstrained<int, 0, 100>::range_size();
  CHECK(y == 101);

}

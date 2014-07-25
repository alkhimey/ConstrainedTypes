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
 * implemented with the "catch" unit testing library.
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


int f1(int x) {
  return x;
}

int f2(month_t x) {
  return x;
}

month_t f3(int x) {
  return x;
}

month_t f4(month_t x) {
  return x;
}

/////////////////////////////////////////////////
///                                           ///
/// Test cases start here                     ///
///                                           ///
/////////////////////////////////////////////////

TEST_CASE( "basic" ) {
  ct::RangeConstrained<int, 15, 100> x = 50;
  CHECK_NOTHROW(x = 15);
  CHECK_NOTHROW(x = 100);
  CHECK( x == 100 );

  CHECK_THROWS(x = 14);
  CHECK_THROWS(x = 101);
}



//TODO: There is actually a bug in this example!
TEST_CASE( "demo", "The demo used in the readme that demonstrates usefullness of this idiom" ) {
  int  revenue[(int)month_t::range_size()];
  
  month_t m;
  while (m < month_t::last()) {
    revenue[m] = 10000;
    m++;
  }

}


TEST_CASE( "enum" ) {
  ct::RangeConstrained<enum E, B, D> e = C;
  
  CHECK_THROWS(e = E);
  CHECK_THROWS(e = A);
  CHECK(e == C);
  CHECK_NOTHROW(e = D);
  CHECK(e == D);
}


TEST_CASE( "basic addition" ) {
  ct::RangeConstrained<int, 15, 130> x = 50;
  
  CHECK_NOTHROW(x = x + 15);
  CHECK_NOTHROW(x = x + x);
  CHECK( x == 130 );
  
  CHECK_THROWS(x = x + 1);
  
}

TEST_CASE( "basic substraction" ) {
  ct::RangeConstrained<int, 0, 100> x = 15;
  
  CHECK_NOTHROW(x = x - 15);
  CHECK_NOTHROW(x = x - x);
  CHECK( x == 0 );
  
  CHECK_THROWS(x = x - 1);
  
}

TEST_CASE( "unary substraction and addition" ) {
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

TEST_CASE( "basic comparison" ) {
  ct::RangeConstrained<int, 0, 100> x = 100;
  ct::RangeConstrained<int, 0, 100> y = 0;
  int z = -2;
  
  CHECK( x != y);
  CHECK( x > y);
  CHECK( x >= y);
  CHECK( y < x);
  CHECK( y <= x);

  CHECK( x != z);
  CHECK( x > z);
  CHECK( x >= z);
  CHECK( z < x);
  CHECK( z <= x);
}

TEST_CASE( "attributes" ) {
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
}

/*
TEST_CASE( "inception" ) {
  ct::RangeConstrained<int, 0, 100> a = 54;
  ct::RangeConstrained< ct::RangeConstrained< int, 0, 100 > , 50, 120 > b = 55;
  int x;

  SECTION( "outside in 1" ) {
    CHECK_NOTHROW(b = a);
    CHECK(b == 54);
  }

  SECTION( "outside in 2" ) {
    CHECK_NOTHROW(b = 53);
    CHECK(b == 53);
  }

  SECTION( "inside out 1" ) {
    CHECK_NOTHROW(a = b);
    CHECK(a == 55);
  }

  SECTION( "inside out 2" ) {
    CHECK_NOTHROW(x = b);
    CHECK(x == 55);
  }

  SECTION( "non overlapping parts") {
    CHECK_THROWS(b = 120);
    CHECK_THROWS(b = 0);
  }
  }*/

TEST_CASE( "mixed types" ) {
  ct::RangeConstrained<int, 0, 100> a = 50;
  ct::RangeConstrained<short, 0, 100> b = 25;
  short x = 20;

  CHECK_NOTHROW(a = b);
  CHECK_NOTHROW(b = a);
  CHECK_NOTHROW(a = a + b);
  CHECK_NOTHROW(b = b + a);

  CHECK_NOTHROW(a = x);
  CHECK_NOTHROW(x = a);
}


TEST_CASE(" function compatiabillity ") {
  month_t a = 6;
  
  SECTION(" parameter is int ") {
    CHECK(f1(1) == 1);
    CHECK(f2(1) == 1);
    CHECK(f3(1) == 1);
    CHECK(f4(1) == 1);
  }

  SECTION(" parameter is constrained type ") {
    CHECK(f1(a) == 6);
    CHECK(f2(a) == 6);
    CHECK(f3(a) == 6);
    CHECK(f4(a) == 6);
  }

  SECTION(" parameter is  out of range ") {
    CHECK(f1(13) == 13);
    CHECK_THROWS(f2(13));
    CHECK_THROWS(f3(13));
    CHECK_THROWS(f4(13));
  }
}

TEST_CASE(" array access ") {
  int  a[5];
  ct::RangeConstrained<int, 0, 4> x = 3;

  CHECK_NOTHROW(a[x] = 5);
  CHECK_NOTHROW(a[5] = x);
  CHECK_NOTHROW(x = a[5]);
}


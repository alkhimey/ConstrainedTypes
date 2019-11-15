/**
 * @author  Artium Nihamkin <artium@nihamkin.com>
 * @date May 2014 
 *
 * @section LICENSE
 *
 * The MIT License (MIT)
 * Copyright © 2014-2019 Artium Nihamkin, http://nihamkin.com
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

/* https://stackoverflow.com/questions/36296425 */
template <typename T>
constexpr bool is_lvalue(T&&) {
  return std::is_lvalue_reference<T>{};
}

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

TEST_CASE( "negative" ) {
  ct::RangeConstrained<int, -100, 100> x = -0;
  CHECK_NOTHROW(x = 100);
  CHECK_NOTHROW(x = -100);
  CHECK( x == -100);

  CHECK_THROWS(x = -101);
  CHECK_THROWS(x = 101);

  CHECK(ct::RangeConstrained<int, -100, 100>::first() == -100);
  CHECK(ct::RangeConstrained<int, -100, 100>::last() == 100);
  CHECK(ct::RangeConstrained<int, -100, 100>::range_size() == 201);
}

TEST_CASE( "const construction" ) {
  const ct::RangeConstrained<int, 15, 100> x1 = 50;
  CHECK( x1 == 50 );

  const int a = 50;
  ct::RangeConstrained<int, 15, 100> x2 = a;
  CHECK( x2 == 50 );

  const ct::RangeConstrained<int, 15, 100> x3 = a;
  CHECK( x3 == 50 );

  // Can't test this with Catch
  //CHECK_THROWS(  const ct::RangeConstrained<int, 15, 100> x4 = 101);
}


TEST_CASE( "demo", "The demo used in the readme that demonstrates usefullness of this idiom" ) {
  month_t m = 1;
  CHECK_NOTHROW(m = 2); // OK
  CHECK_THROWS(m = 13);  // "The value 13 is out of the range [1, 12]"
}


TEST_CASE( "demo2", "The demo used in the readme that demonstrates compatibility" ) {
  month_t m = 12;
  CHECK_NOTHROW(f1(m)); // OK
  CHECK_THROWS(f4(13)); // Exception
}


TEST_CASE( "enum" ) {
  ct::RangeConstrained<enum E, B, D> e = C;
  
  CHECK_THROWS(e = E);
  CHECK_THROWS(e = A);
  CHECK(e == C);
  CHECK_NOTHROW(e = D);
  CHECK(e == D);
}


TEST_CASE( "char" ) {
  ct::RangeConstrained<char, 'a', 'z'> ch = 'a';

  CHECK_THROWS(ch = '%');  
  CHECK_THROWS(ch = 'a' - 1);
  CHECK_THROWS(ch = 'z' + 1);
  CHECK(ch == 'a');
  CHECK_NOTHROW(ch = 'd');
  CHECK(ch == 'd');
  CHECK(ct::RangeConstrained<char, 'a', 'z'>::first() == 'a');
  CHECK(ct::RangeConstrained<char, 'a', 'z'>::last() == 'z');
}


TEST_CASE( "bool" ) {

  SECTION("basic bool range cheking") {
    ct::RangeConstrained<bool, true, true> bool_only_true = true;
  
    CHECK_THROWS(bool_only_true = false);
    CHECK(bool_only_true == true);
    CHECK_NOTHROW(bool_only_true = true);

    CHECK(ct::RangeConstrained<bool, true, true>::first() == true);
    CHECK(ct::RangeConstrained<bool, true, true>::last() == true);
    CHECK(ct::RangeConstrained<bool, true, true>::range_size() == 1);
  }

  SECTION("assign with implicit casting to bool") {
    ct::RangeConstrained<bool, false, true> bool_false_true = true;
    CHECK_NOTHROW(bool_false_true = 3);
    CHECK_NOTHROW(bool_false_true = 0);
  }
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
    CHECK( x == 100 );
    CHECK_THROWS(x++);
    CHECK( x == 100 );
  
    CHECK_NOTHROW(y--);
    CHECK( y == 0 );
    CHECK_THROWS(y--);
    CHECK( y == 0 );
  }

  SECTION( "pre" ) {
    CHECK_NOTHROW(++x);
    CHECK( x == 100 );
    CHECK_THROWS(++x);
    CHECK( x == 100 );
    
    CHECK_NOTHROW(--y);
    CHECK( y == 0 );
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


TEST_CASE( "function compatiabillity" ) {
  month_t a = 6;
  
  SECTION(" parameter is int ") {
    CHECK(f1(1) == 1);
    CHECK(f2(1) == 1);
    CHECK(f3(1) == 1);
    CHECK(f4(1) == 1);
  }

  SECTION( "parameter is constrained type" ) {
    CHECK(f1(a) == 6);
    CHECK(f2(a) == 6);
    CHECK(f3(a) == 6);
    CHECK(f4(a) == 6);
  }

  SECTION( "parameter is out of range" ) {
    CHECK(f1(13) == 13);
    CHECK_THROWS(f2(13));
    CHECK_THROWS(f3(13));
    CHECK_THROWS(f4(13));
  }
}


TEST_CASE( "array access" ) {
  int  a[5];
  ct::RangeConstrained<int, 0, 4> x = 3;

  CHECK_NOTHROW(a[x] = 5);
  CHECK_NOTHROW(a[3] = x);
  CHECK_NOTHROW(x = a[3]);

  a[3] = 6;
  CHECK_THROWS(x = a[3]);
}

TEST_CASE( "intermidiate overflows", "overflows in intermidiate operations are allowed") {
  ct::RangeConstrained<int, 1, 4> x = 3;
  ct::RangeConstrained<int, 1, 4> y = 2;
  int z;

  CHECK_NOTHROW(x = (x + y) - y);
  CHECK(x == 3);
  CHECK_NOTHROW(x = (x + 2) - 2);
  CHECK(x == 3);
  CHECK_NOTHROW(x = (x - 5*y) + 5*y);
  CHECK(x == 3);  
  CHECK_NOTHROW(x = (x - 5) + 5);
  CHECK(x == 3);  
  CHECK_NOTHROW(x = (x * y) / y);
  CHECK(x == 3);
  CHECK_NOTHROW(x = (x * 5) / 5);
  CHECK(x == 3);

  CHECK_THROWS(x = (x + y + y + y));
  CHECK_NOTHROW(z = (x + y + y + y));
  CHECK_NOTHROW(x = (x + y + y + y) - y -y -y -y);
  CHECK(x == 1);
}


TEST_CASE( "explicit casting") {
  month_t m = 5;
  int k;
  
  CHECK_NOTHROW(k = (int)m); // Notice that underlying of month_t is short
  CHECK(k == 5);

  CHECK_NOTHROW(m = (month_t)k);
  CHECK(k == 5);
  
  CHECK_THROWS(m = (month_t)13);
  CHECK_THROWS(k = (int)(month_t)13);
}

TEST_CASE( "unary substraction/addition operator order of evaluation") {
  month_t m = 10;
  month_t m2;

  SECTION(" prefix operation should modify the the veriable first ") {
    
    SECTION("increment") {
      m2 = ++m;
      CHECK(m  == 11);
      CHECK(m2 == 11);
    }

    SECTION("decrement") {
      m2 = --m;
      CHECK(m  == 9);
      CHECK(m2 == 9);
    }
  }

  SECTION(" postfix operation should modify the the veriable after ") {
    
    SECTION("increment") {
      m2 = m++;
      CHECK(m  == 11);
      CHECK(m2 == 10);
    }

    SECTION("decrement") {
      m2 = m--;
      CHECK(m  == 9);
      CHECK(m2 == 10);
    }
  }

  SECTION(" prefix chaining ") {

    SECTION("increment") {
      m2 = ++++m;
      CHECK(m  == 12);
      CHECK(m2 == 12);
    }

    SECTION("decrement") {
      m2 = ----m;
      CHECK(m  == 8);
      CHECK(m2 == 8);
    }
  }

  /* No postfix chaining - compilation error should occur */

  SECTION(" postfix returns const by value which is not lvalue ") {

    SECTION("increment") {
      CHECK_FALSE(is_lvalue(m++));  
    }

    SECTION("decrement") {
      CHECK_FALSE(is_lvalue(m--));
    }
  }

  SECTION(" prefix returns by reference which is an lvalue ") {

    SECTION("increment") {
      CHECK(is_lvalue(++m));  
    }

    SECTION("decrement") {
      CHECK(is_lvalue(--m));
    }
  }
}

TEST_CASE( "sizeof operator") {

  SECTION("unsigned integers") {
    ct::RangeConstrained<uint16_t, 1, 4> u16 = 3;
    ct::RangeConstrained<uint32_t, 1, 4> u32 = 3;
    ct::RangeConstrained<uint64_t, 1, 4> u64 = 3; 

    CHECK(sizeof(u16) == sizeof(uint16_t));
    CHECK(sizeof(u32) == sizeof(uint32_t));
    CHECK(sizeof(u64) == sizeof(uint64_t));
  }

  SECTION("signed integers") {
    ct::RangeConstrained<int16_t, 1, 4> i16 = 3;
    ct::RangeConstrained<int32_t, 1, 4> i32 = 3;
    ct::RangeConstrained<int64_t, 1, 4> i64 = 3; 

    CHECK(sizeof(i16) == sizeof(int16_t));
    CHECK(sizeof(i32) == sizeof(int32_t));
    CHECK(sizeof(i64) == sizeof(int64_t));
  }


  SECTION("other base types") {

    ct::RangeConstrained<char, 'a', 'z'> ch = 'd';
    ct::RangeConstrained<bool, false, true> b = false;

    CHECK(sizeof(ch) == sizeof(char));
    CHECK(sizeof(b) == sizeof(bool));
  }
}

TEST_CASE("invalid range", "last is smaller than first, the type does not have a value") {

  ct::RangeConstrained<int, 10, -10> no_value;

  CHECK_THROWS(no_value = 0);
  CHECK_THROWS(no_value = 10);
  CHECK_THROWS(no_value = -10);

  CHECK_THROWS(no_value = 11);
  CHECK_THROWS(no_value = -11);

  CHECK(ct::RangeConstrained<int, 10, -10>::first() == 10);
  CHECK(ct::RangeConstrained<int, 10, -10>::last() == -10);
  CHECK(ct::RangeConstrained<int, 10, -10>::range_size() == 0);
}

TEST_CASE("big range_size") {
  SECTION("16 bit unsigned") {
    CHECK(ct::RangeConstrained<uint16_t, numeric_limits<uint16_t>::min(), numeric_limits<uint16_t>::max()>::range_size() == 65536);
  }

  SECTION("16 bit signed") {
    CHECK(ct::RangeConstrained<int16_t, numeric_limits<int16_t>::min(), numeric_limits<int16_t>::max()>::range_size() == 65536);
  }

  SECTION("32 bit unsigned") {
    CHECK(ct::RangeConstrained<uint32_t, numeric_limits<uint32_t>::min(), numeric_limits<uint32_t>::max()>::range_size() == 0x100000000);
  }

  SECTION("32 bit signed") {
    CHECK(ct::RangeConstrained<int32_t, numeric_limits<int32_t>::min(), numeric_limits<int32_t>::max()>::range_size() == 0x100000000);
  }

  SECTION("64 bit unsigned") {
    CHECK(ct::RangeConstrained<uint64_t, numeric_limits<uint64_t>::min(), numeric_limits<uint64_t>::max()>::range_size() == 0xffffffffffffffff + 1);
  }

  SECTION("64 bit signed") {
    CHECK(ct::RangeConstrained<int64_t, numeric_limits<int64_t>::min(), numeric_limits<int64_t>::max()>::range_size() == 0xffffffffffffffff + 1);
  }
}


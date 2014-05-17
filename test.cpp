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
 * This file constains unit tests of the RangeConstrained library. The unit tests are
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


TEST_CASE( "Simple test", "a" ) {
  ct::RangeConstrained<int, 15, 100> x = 50;
  x = 15;
  x = 100;
  REQUIRE( x == 100 );
}

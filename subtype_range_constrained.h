/**
 * @author  Artium Nihamkin <artium@nihamkin.com>
 * @version 1.0.0
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
 * This library allows definition of range constrained subtypes of discreete types.
 * Variables of these types are limited to hold types of a defined range.
 *
 * Usage example:
 * 	 ct::RangeConstrained<short, 1, 12> month;
 *
 * Assgning a value to a variable that is out of the range of the subtype will cause
 * an std::out_of_range exception to be thrown.
 * 
 * Variables of the subtype are fully compatiable with the base type and can substitute
 * it's variables.
 */


#ifndef SUBTYPE_RANGE_CONSTRAINED_H
#define SUBTYPE_RANGE_CONSTRAINED_H

#include <stdexcept>
#include <sstream>
#include <string>

namespace ConstrainedTypes {


template<class T, T First, T Last>
class RangeConstrained {

private:
  T _val;
  
  inline static const T& range_check(const T& val) {
    if ((val < First) || (val > Last)) {
      std::ostringstream strm;
      strm << "The value " << val << " is outside the range " << "[" << First << ", " << Last << "]";
      throw std::out_of_range (strm.str());
    }
    return val;
  }

public:
  
  RangeConstrained() : _val(First) {}
  RangeConstrained(const T& val) : _val(range_check(val)) {}
  
  inline T first(void) const {
    return First;
  }

  inline T last(void) const {
    return First;
  }

  inline operator T () {
    return _val;
  }
 
  /// Allows assignment between different range constrained instantiations.
  template<class T2, T2 F, T2 L>
  inline operator RangeConstrained<T2, F, L> () {
    return RangeConstrained<T2, F, L>(_val);
  }

  inline RangeConstrained& operator += (const T& val) {
    _val += val;
    return *this;
  }

  inline RangeConstrained& operator -= (const T& val) {
    _val -= val;
    return *this;
  }

  inline RangeConstrained& operator *= (const T& val) {
    _val *= val;
    return *this;
   }

   inline RangeConstrained& operator /= (const T& val) {
    _val /= val;
    return *this;
   }

  inline RangeConstrained& operator %= (const T& val) {
    _val %= val;
    return *this;
  }

  inline RangeConstrained& operator ++() {
    _val++;
    return *this;
  }

  inline RangeConstrained& operator --() {
    _val--;
    return *this;
  }

  inline RangeConstrained& operator ++(int) {
    _val++;
    return *this;
  }

  inline RangeConstrained& operator --(int) {
    _val--;
    return *this;
  }


};

}

namespace ct = ConstrainedTypes;

#endif

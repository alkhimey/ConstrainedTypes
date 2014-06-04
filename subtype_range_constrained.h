/**
 * @author  Artium Nihamkin <artium@nihamkin.com>
 * @version 1.0.1
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
 * This library allows definition of range constrained subtypes of discrete types.
 * Variables of these types are limited to contain values of a defined range.
 *
 * Usage example:
 * 	 ct::RangeConstrained<short, 1, 12> month;
 *
 * Notice that the range boundaries are inclusive: month can hold values between 1 to 12 including 1 and 12.
 *
 * Assigning a value to a variable that is out of the range of the subtype will cause
 * an exception to be thrown.
 * 
 * Variables of the subtype are fully compatible with the base type and can substitute
 * it's variables.
 *
 */


#ifndef SUBTYPE_RANGE_CONSTRAINED_H
#define SUBTYPE_RANGE_CONSTRAINED_H

#include <stdexcept>
#include <sstream>
#include <string>
#include <limits>

namespace ConstrainedTypes {

template<class T, T First, T Last>
class RangeConstrained {
public:

  /// Custom exception used to indicate that value was out of range.
  class constraint_error : public std::out_of_range {
  private:
    const T _val, _first, _last;
    
    static std::string to_string( const T& n ){
      std::ostringstream stm ;
      stm << n ;
      return stm.str() ;
    }
    
  public:
    constraint_error(T val, T first, T last) : _val(val), _first(first), _last(last), 
					       std::out_of_range("The value " + to_string(val) + " is out of the range [" + 
								 to_string(first) + ", " + to_string(last) + "]") {}
    inline const T getVal() const { return _val;}
    inline const T getFirst() const { return _first;}
    inline const T getLast() const { return _last;}
  };
  
private:
  T _val;
  
  inline static const T& range_check(const T& val) {
    if ((val < First) || (val > Last)) {
      throw constraint_error (val, First, Last);
    }
    return val;
  }

public:
  
  RangeConstrained() : _val(First) {}
  RangeConstrained(const T& val) : _val(range_check(val)) {}
  
  
  inline static T first(void)  {
    return First;
  }

  inline static T last(void) {
    return Last;
  }

  inline static T range_size(void)  {
    return Last - First + 1;
  }

  inline operator T () const {
    return _val;
  }
 
  /// Allows assignments between different range constrained instantiations.
  template<class T2, T2 F, T2 L>
  inline operator RangeConstrained<T2, F, L> () const {
    return RangeConstrained<T2, F, L>(_val);
  }

  inline RangeConstrained& operator += (const T& other) {
    //if(std::numeric_limits<T>::max() - other > _val)
    //  throw std::out_of_range ("Out of the base type range");

    T temp = _val;
    temp += other;
    _val = range_check(temp);
    return *this;
  }

  inline RangeConstrained& operator -= (const T& other) {
    T temp = _val;
    temp -= other;
    _val = range_check(temp);
    return *this;
  }

  inline RangeConstrained& operator *= (const T& other) {
    T temp = _val;
    temp *= other;
    _val = range_check(temp);
    return *this;
   }

   inline RangeConstrained& operator /= (const T& other) {
    T temp = _val;
    temp /= other;
    _val = range_check(temp);
    return *this;
   }

  inline RangeConstrained& operator %= (const T& other) {
    T temp = _val;
    temp %= other;
    _val = range_check(temp);
    return *this;
  }

  inline RangeConstrained& operator ++() {
    T temp = _val;
    temp++;
    _val = range_check(temp);
    return *this;
  }

  inline RangeConstrained& operator --() {
    T temp = _val;
    temp--;
    _val = range_check(temp);

  }

  inline RangeConstrained& operator ++(int) {
    T temp = _val;
    ++temp;
    _val = range_check(temp);
  }

  inline RangeConstrained& operator --(int) {
    T temp = _val;
    --temp;
    _val = range_check(temp);

  }


};

}

namespace ct = ConstrainedTypes;

#endif

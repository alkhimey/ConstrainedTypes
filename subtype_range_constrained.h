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
 
  // Allows compatibility between different range constrained instantiations.
  template<T F, T L>
  inline operator RangeConstrained<T, F, L> () {
    return RangeConstrained<T, F, L>(_val);
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

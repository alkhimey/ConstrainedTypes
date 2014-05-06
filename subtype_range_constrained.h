#ifndef SUBTYPE_RANGE_CONSTRAINED_H
#define SUBTYPE_RANGE_CONSTRAINED_H

#include <stdexcept>

namespace ConstrainedTypes {


template<class T, T First, T Last>
class RangeConstrained {

private:
  T _val;
  
  inline static const T& range_check(const T& val) {
    if ((val < First) || (val > Last))
      throw std::out_of_range ("Value is out of type's range.");
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

  operator T () {
    return _val;
  }
 
  // Allows compatibility between different range constrained instantiations.
  template<T F, T L>
  operator RangeConstrained<T, F, L> () {
    return RangeConstrained<T, F, L>(_val);
  }

  RangeConstrained& operator += (const T& val) {
    _val += val;
    return *this;
  }

  RangeConstrained& operator -= (const T& val) {
    _val -= val;
    return *this;
  }

  RangeConstrained& operator *= (const T& val) {
    _val *= val;
    return *this;
   }

   RangeConstrained& operator /= (const T& val) {
    _val /= val;
    return *this;
   }

  RangeConstrained& operator %= (const T& val) {
    _val %= val;
    return *this;
  }

};

}

namespace ct = ConstrainedTypes;

#endif

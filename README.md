ConstrainedTypes
================

This library allows definition of range constrained subtypes of integral types.

It is similar to what is provided by [Ada's range
keyword](https://en.wikibooks.org/wiki/Ada_Programming/Types/range).

Using this library, it is possible define a new type which can store values
from a range. Assigning a value to a variable of this type will cause the value
to be checked for validity. If it is outside the valid range, an exception will
be raised. 

These "automatic assertions" increase type safety of programs and help catching
bugs early.

Example
-------

```C++
#include "subtype_range_constrained.h"

typedef ct::RangeConstrained<short, 1, 12> month_t;

int main(void) {
    month_t m = 1; // OK
    m = 12; // OK
    m  = 13; // Exception!
    return 0;
}
```

Features
--------
* Any integral type can be used including `char` and enumerations.
* Subtypes has full compatibility with their underlying type.
* Subtypes has the same memory representation as their underlying type.
* Range checking is performed only during assignment.
* Simple implementation and extensive test suite.

Use Cases
----------
* Sub-type of `char` that represents only the lower case letters.
  ```C++
  typedef ct::RangeConstrained<char, 'a', 'z'> lower_alpha_t;
  ```
* Assuring that variables that supposed to store enums are not assigned a value
  which is not in the range of representable values for that enum. Note that
  there are sanitizers that will perform compile time check for this behavior.
  For example
  [UBSan's](https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html#available-checks)
  `-fsanitize=enum`.
  ```C++
  enum color_enum {RED = 0, GREEN = 1, BLUE = 2};
  typedef ct::RangeConstrained<color_enum, RED, BLUE> Color;
  void setBackground(Color color);
  ...
  setBackground(3); // Exception!
  ```
* Physical quantities like speed or altitude have intrinsic constrains. 
  Thus out of range value is an indication of a bug.
  ```C++
  typedef ct::RangeConstrained<int32_t, -2000, 100000> AltitudeFeetAboveSeaLevel;
  ```
* Values that represent quantity or count:
  ```C++
  ct::RangeConstrained<uint8_t, 0, 5> occupiedSeats;
  occupiedSeats = 7; // Exception!
  ```
* Indexes passed to a function. Note that for checking out of bounds access to
  arrays it is possible to use `vectors`.
  ```C++
  #define STATIONS 8
  ct::RangeConstrained<uint8_t, 0, STATIONS - 1> StationID;
  Data * getData(StationID stationID);
  ...
  Data *data = getData(8); // Exception!
  ```

Handling the Exception
---------------------
```C++
#include <iostream>
#include "subtype_range_constrained.h"

typedef ct::RangeConstrained<short, 1, 12> month_t;

int main(void) {
    try {
        month_t m = 13; 
    } catch(const month_t::constraint_error& e) {
        std::cerr << e.what() << '\n';
        std::cerr << e.getFirst() << '\n';
        std::cerr << e.getLast() << '\n';
        std::cerr << e.getVal() << '\n';
    }
    return 0;
}
```
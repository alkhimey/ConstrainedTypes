ConstrainedTypes
================

This library allows definition of range constrained subtypes of discreete types.
Variables of these types are limited to hold types of a defined range.

Usage example:

    ct::RangeConstrained<short, 1, 12> month;
    month = 5; // ok
    month = 13; // std::out_of_range exception is thrown

Assgning a value to a variable that is out of the range of the subtype will cause an `std::out_of_range` exception to be thrown.
Variables of the subtype are fully compatiable with the base type and can substitute it's variables.

ConstrainedTypes
================

This library allows definition of range constrained subtypes of discrete types.

Variables of these types are limited to hold values of a defined range. Assigning a value to a variable that is out of the range of the subtype will cause an exception to be thrown.

This idiom was adopted from Ada and is useful for writing safe code. 

For example it can be used to make sure that a variable, that is used as an index of an array, stays within array's boundaries:

```C++
typedef ct::RangeConstrained<short, 1, 12> month_t;

int  revenue[(int)month_t::range_size()];
month_t m;
while (m < month_t::last()) {
  revenue[m] = 10000;
  m++;
}
```

Notice that the range boundaries are inclusive.

Any discreet type can be used as a base, including enums:

```C++
enum DAY {  SUN, MON, TUE, WED, THU, FRI, SAT }; 

ct::RangeConstrained<enum DAY, SUN, THU> current_workday;
```

Variables of the subtype are fully compatible with the base type and can substitute it's variables in any scenario.


TODO:
------
- [ ] Finish writing tests.
- [ ] Create a safe array template whose [] operator is parameterize to be only a constrained type.
- [ ] Check if an operation's result is out of range of the base type. Use numeric_limits and be cautious as even the "%" operator can cause overflows.
- [ ] Allow custom overflow handling.

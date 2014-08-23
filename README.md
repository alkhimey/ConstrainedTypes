ConstrainedTypes
================

This library allows definition of range constrained subtypes of discrete types, similar to Ada's range keyword.

Variables of these types are limited to hold values from the defined range. Assigning a value that is out of the range of the subtype will cause an exception to be thrown.

```C++
typedef ct::RangeConstrained<short, 1, 12> month_t;

int main(void) {
	month_t m = 1;
	m = 12; // OK
	m = 13; // Exception with the message: "The value 13 is out of the range [1, 12]"
}
```

Any discreet type can be used as a base, including enums:

```C++
enum DAY {  SUN, MON, TUE, WED, THU, FRI, SAT }; 

ct::RangeConstrained<enum DAY, SUN, THU> current_workday;
```

Variables of the subtype are fully compatible with the underlying type and can substitute it's variables in any scenario.

```C++
typedef ct::RangeConstrained<short, 1, 12> month_t;</p>

void f1(int x) {return;}
void f2(month_t m) {return;}

<p>int main(void) {
    month_t m = 1;
    f1(m);  // OK
    f2(12); // OK 
    f2(13); // Exception
}
```

Range checking is performed only during the assignment, therfore intermidiate opertations can be out of range.

```C++
ct::RangeConstrained<int, 1, 4> x = 3;
ct::RangeConstrained<int, 1, 4> y = 2;
int z;
	
x = x + y; // Exception
z = x + y; // OK
x = (x + y) - y; // OK

```

Further Work:
------
- [ ] Create a safe array template whose [] operator is parameterize to be only a constrained type.
- [ ] Allow custom overflow handling.(?)

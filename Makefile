TESTS_BINARY = run_tests.out

tests: test.cpp subtype_range_constrained.h catch.hpp
	g++ -Wall -Werror test.cpp -o $(TESTS_BINARY)

clean:
	rm -f $(TESTS_BINARY)

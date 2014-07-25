TESTS_BINARY = test.o

tests: test.cpp subtype_range_constrained.h catch.hpp
	g++ test.cpp -o $(TESTS_BINARY)

run_tests: 
	./$(TESTS_BINARY)

clean:
	rm -f $(TESTS_BINARY)

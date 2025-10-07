all:
	g++ -std=c++20 device.cpp -o a.out

test:
	g++ -std=c++20 tests/test_separator.cpp -lgtest -lgtest_main -pthread -o test_separator

clean:
	rm -f a.out test_separator

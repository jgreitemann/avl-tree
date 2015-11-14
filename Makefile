CFLAGS = -g -O3 -Wall -std=c++11

.PHONY: clean

avl_test: avl_test.cpp avl_tree.hpp
	$(CXX) $(CFLAGS) $(DEFINES) -o $@ $<

clean:
	$(RM) avl_test

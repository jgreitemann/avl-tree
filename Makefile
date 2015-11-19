CFLAGS = -g -O3 -Wall -std=c++11
CP = cp
ifndef PREFIX
PREFIX = /usr/local
endif

.PHONY: clean install uninstall

avl_test: avl_test.cpp avl_tree.hpp
	$(CXX) $(CFLAGS) $(DEFINES) -o $@ $<

clean:
	$(RM) avl_test

install: avl_tree.hpp
	$(CP) avl_tree.hpp $(addprefix $(PREFIX), /include/)

uninstall:
	$(RM) $(addprefix $(PREFIX), /include/avl_tree.hpp)

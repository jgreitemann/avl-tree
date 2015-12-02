CFLAGS += -g -O3 -Wall -std=c++11
ifdef GTEST_INCLUDE_DIR
	CFLAGS += $(addprefix -I,$(GTEST_INCLUDE_DIR))
endif
ifdef GTEST_LIBS
	LD_FLAGS += $(addprefix -L,$(GTEST_LIBS))
endif
LD_FLAGS += -lpthread -lgtest
CP = cp
ifndef PREFIX
PREFIX = /usr/local
endif

.PHONY: test clean install uninstall

all: avl_test

avl_test.o: avl_test.cpp avl_tree.hpp
	$(CXX) -c $(CFLAGS) $(DEFINES) $<

avl_test: avl_test.o
	$(CXX) -o $@ $< $(LD_FLAGS)

test: avl_test
	./avl_test

clean:
	$(RM) avl_test.o avl_test

install: avl_tree.hpp
	$(CP) avl_tree.hpp $(addprefix $(PREFIX), /include/)

uninstall:
	$(RM) $(addprefix $(PREFIX), /include/avl_tree.hpp)

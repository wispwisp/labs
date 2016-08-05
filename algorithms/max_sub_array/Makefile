TEST:=tests

CPP:=g++
CFLAGS:=-lstdc++ -std=c++14 -ggdb -Wall -Wextra -Wshadow -pedantic -Weffc++ -O0
LIBS:=-lboost_system

.PHONY : all clean

all: $(TEST)

$(TEST): test.cpp ../tests.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(LIBS) -lboost_unit_test_framework

clean :
	rm -f $(TEST) *.o *~

DEBUG:=debug
TEST:=tests

CPP:=g++

CFLAGS:=-lstdc++ -std=c++14 -ggdb -Wall -Wextra -Wshadow -pedantic -Weffc++ -O0
TEST_CFLAGS:=-lstdc++ -std=c++14 -Wall -Wextra -Wshadow -pedantic -Weffc++ -O2

LIBS:= #-lboost_system
TEST_LIBS:= -lgtest -lgmock -lpthread

.PHONY : all clean

all: $(TEST) $(DEBUG)

$(DEBUG): main.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(LIBS)

$(TEST): tests.cpp
	$(CPP) $(TEST_CFLAGS) -o $@ $^ $(LIBS) $(TEST_LIBS)

clean :
	rm -f $(TEST) $(DEBUG) *.o *~

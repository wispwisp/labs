TEST:=tests

CPP:=g++
CFLAGS:=-lstdc++ -std=c++17 -ggdb -Wall -Wextra -Wshadow -pedantic -Weffc++ -O0
LIBS:=-lgtest -lgmock -lpthread

.PHONY : all clean

all: $(TEST)

FILES:=\
tests.cpp

$(TEST): $(FILES)
	$(CPP) $(CFLAGS) -o $@ $^ $(LIBS)

clean :
	rm -f $(TEST) *.o *~

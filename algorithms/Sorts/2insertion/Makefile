.PHONY: all clean

NAME:=insertion.out
CPP:=gcc
CFLAGS:=-lstdc++ -std=c++11 -ggdb -Wall -Wextra -Wshadow -pedantic -Weffc++ -O0
LIBS:=

all: $(NAME)

$(NAME): insertion.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(LIBS)
clean:
	rm -f $(NAME) *.o *~

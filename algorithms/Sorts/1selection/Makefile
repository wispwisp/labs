.PHONY : all clean

NAME:=selection.out 
CPP:=gcc
CFLAGS:=-lstdc++ -std=c++11 -ggdb -Wall -Wextra -pedantic -O
LIBS:=

all : $(NAME)

$(NAME) : selection.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(LIBS)
clean :
	rm -f $(NAME) *.o *~

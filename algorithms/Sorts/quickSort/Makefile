.PHONY : all clean

NAME:=quick.out 
CPP:=gcc
CFLAGS:=-lstdc++ -std=c++14 -ggdb -Wall -Wextra -Wshadow -pedantic -Weffc++ -O0
LIBS:=

all : $(NAME)

$(NAME) : quick.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(LIBS)
clean :
	rm -f $(NAME) *.o *~

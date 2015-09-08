.PHONY : all clean

NAME:=a.out 
CPP:=gcc
CFLAGS:=-lstdc++ -std=c++1y -Wall -Wextra -pedantic -O
LIBS:=#-lбиблиотека -Lместо

all : $(NAME)

$(NAME) : main.cpp
	$(CPP) $(CFLAGS) -o $@ $^ $(LIBS)
clean :
	rm -f $(NAME) *.o *~

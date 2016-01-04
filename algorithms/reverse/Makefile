.PHONY: all clean

NAME:=reverse
CPP:=gcc
CFLAGS:=-lstdc++ -std=c++14 -ggdb -Wall -Wextra -Wshadow -pedantic -Weffc++ -O0
LIBS:=

all: $(NAME)

$(NAME): $(NAME).cpp
	$(CPP) $(CFLAGS) -o $@.out $^ $(LIBS)
clean:
	rm -f $(NAME).out *.o *~

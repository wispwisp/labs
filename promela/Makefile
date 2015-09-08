.PHONY : all clean

FORMULA:=-f '<> !cget'

NAME:=pan
CPP:=cc
CFLAGS:=
LIBS:=

all : $(NAME)

$(NAME) :
	spin $(FORMULA) -a student.spin
	cc -o $(NAME) pan.c
clean :
	rm -f $(NAME) *.o *~ pan.* student.spin.*

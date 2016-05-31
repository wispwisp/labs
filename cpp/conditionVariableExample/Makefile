TEST=tests.out
NAME=a.out

OPTIMIZATION=-ggdb -O0
WARNINGS=-Wall
FLAGS=-std=c++11 $(WARNINGS)

.PHONY: clean all

$(NAME): main.cpp
	g++ $^ $(FLAGS) $(OPTIMIZATION) -o$@ -pthread

test: $(TEST)
$(TEST): tests.cpp
	g++ $^ $(FLAGS) $(OPTIMIZATION) -o $@ -lboost_system -lboost_unit_test_framework
	./$(TEST)

clean:
	rm -rf $(NAME) $(TEST) *.a *.o *.so *.so.*

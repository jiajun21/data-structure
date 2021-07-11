FLAGS = -Wall -I../include/

.PHONY: all
all: test_sort test_sort_2

test_sort: test_sort.c ../src/sort.c ../include/sort.h
	gcc -o test_sort $(FLAGS) test_sort.c ../src/sort.c
test_sort_2: test_sort_2.c ../src/sort.c ../include/sort.h
	gcc -o test_sort_2 $(FLAGS) test_sort_2.c ../src/sort.c

clean:
	rm test_sort test_sort_2

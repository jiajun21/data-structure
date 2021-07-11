FLAGS = -Wall -I../include/

.PHONY: all
all: test_list test_stack test_queue test_tree test_tree_2 \
		test_heap test_heap_2 test_hashtable test_graph

test_list: test_list.c ../src/list.c ../include/list.h
	gcc -o test_list $(FLAGS) test_list.c ../src/list.c
test_stack: test_stack.c ../src/stack.c ../include/stack.h
	gcc -o test_stack $(FLAGS) test_stack.c ../src/stack.c
test_queue: test_queue.c ../src/queue.c ../include/queue.h
	gcc -o test_queue $(FLAGS) test_queue.c ../src/queue.c
test_tree: test_tree.c ../src/tree.c ../include/tree.h
	gcc -o test_tree $(FLAGS) test_tree.c ../src/tree.c
test_tree_2: test_tree_2.c ../src/tree.c ../include/tree.h
	gcc -o test_tree_2 $(FLAGS) test_tree_2.c ../src/tree.c
test_heap: test_heap.c ../src/heap.c ../include/heap.h
	gcc -o test_heap $(FLAGS) test_heap.c ../src/heap.c
test_heap_2: test_heap_2.c ../src/heap.c ../include/heap.h
	gcc -o test_heap_2 $(FLAGS) test_heap_2.c ../src/heap.c
test_hashtable: test_hashtable.c ../src/hashtable.c ../include/hashtable.h
	gcc -o test_hashtable $(FLAGS) test_hashtable.c ../src/hashtable.c
test_graph: test_graph.c ../src/graph.c ../include/graph.h
	gcc -o test_graph $(FLAGS) test_graph.c ../src/graph.c

clean:
	rm test_list test_stack test_queue test_tree test_tree_2 \
		test_heap test_heap_2 test_hashtable test_graph

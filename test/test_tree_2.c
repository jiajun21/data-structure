#include "tree.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

/* usage: ./test_tree_2 <op_time> */
int main(int argc, char * argv[])
{
    tree T;
    int op_time;
    clock_t start, end;

    assert(argc == 2);

    op_time = atoi(argv[1]);

    T = createTree();
    assert(T != NULL);

    srand((unsigned int)time(NULL));

#ifdef NO_RECURSIVE
    printf("\nno recursive version\n");
#else
    printf("\nrecursive version\n");
#endif /* NO_RECURSIVE */

    printf("total operation number: %d\n\n", op_time);

    start = clock();
    for (int i = 0; i < op_time; i++)
    {
        insertElement(T, rand() % 1000);
    }
    end = clock();
    printf("total insert time:   %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("average insert time: %lf\n\n", (double)(end - start) / CLOCKS_PER_SEC / op_time);

    start = clock();
    for (int i = 0; i < op_time; i++)
    {
        findElement(T, rand() % 1000);
    }
    end = clock();
    printf("total find time:     %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("average find time:   %lf\n\n", (double)(end - start) / CLOCKS_PER_SEC / op_time);

    start = clock();
    for (int i = 0; i < op_time; i++)
    {
        deleteElement(T, rand() % 1000);
    }
    end = clock();
    printf("total delete time:   %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
    printf("average delete time: %lf\n\n", (double)(end - start) / CLOCKS_PER_SEC / op_time);

    destroyTree(T);

    return 0;
}
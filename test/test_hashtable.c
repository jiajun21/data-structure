#include "hashtable.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct data
{
    char buf[128];
};

void printHashtable(hashtable HT, nodeptr target);

int main(int argc, char * argv[])
{
    hashtable HT;
    struct data * dataptr;
    unsigned int size;
    int ret, option;
    char key[128];
    nodeptr target;

    dataptr = (struct data *)malloc(sizeof(sizeof(struct data)));
    assert(dataptr != NULL);
    strcpy(dataptr->buf, "hello, world!\n");

    printf(">> hashtable size: ");
    ret = scanf("%u", &size);
    assert(ret == 1);
    printf("\n");

    HT = createHashtable(size);
    assert(HT != NULL);

    printHashtable(HT, NULL);
    printf("\n");

    while (1)
    {
        printf(">> 0. insert\n");
        printf("   1. find\n");
        printf("   2. delete\n");
        printf("   3. quit\n");
        printf(">> ");
        ret = scanf("%d", &option);
        assert(ret == 1);

        if (option == 3)
            break;

        printf(">> Key: ");
        /* assert key[128] is enough */
        ret = scanf("%s", key);
        assert(ret == 1);

        switch (option)
        {
        case 0:
            ret = insertElement(HT, key, (void *)dataptr);
            assert(ret != -1);
            target = NULL;
            break;
        case 1:
            target = findElement(HT, key);
            if (target == NULL)
                printf("   not found\n");
            break;
        case 2:
            ret = deleteElement(HT, key);
            if (ret == -1)
                printf("   no deletion\n");
            target = NULL;
            break;
        default:
            break;
        }

        printHashtable(HT, target);
        printf("\n");
    }

    destroyHashtable(HT);
    free(dataptr);

    return 0;
}

static int _getItemWidth_unsigned(int n)
{
    int ret;

    ret = 1;

    while (n > 9)
    {
        n /= 10;
        ret += 1;
    }

    return ret;
}

static int _getItemWidth_string(char * str)
{
    int ret;

    ret = strlen(str);

    return ret;
}

void printHashtable(hashtable HT, nodeptr target)
{
    int width1, width2, width3, tmp;

    printf("    hashtable->size\n");
    printf("        %u\n", HT->size);

    printf("    hashtable->stock\n");
    printf("        %u\n", HT->stock);

    printf("    hashtable->table\n");

    width1 = _getItemWidth_unsigned(HT->size - 1);
    width2 = 8; /* charater num of "inserted" */
    width3 = 0;
    for (int i = 0; i < HT->size; i++)
    {
        if (HT->table[i].s == inserted)
        {
            tmp = _getItemWidth_string(HT->table[i].key);
            if (tmp > width3)
                width3 = tmp;
        }
    }
    if (target != NULL)
        width3 += 2;

    for (int i = 0; i < HT->size; i++)
    {
        printf("        %*u  ", width1, i);
        if (HT->table[i].s == empty)
            printf("%*s\n", -1 * width2, "empty");
        else if (HT->table[i].s == deleted)
            printf("%*s\n", -1 * width2, "deleted");
        else
        {
            printf("%*s  ", -1 * width2, "inserted");
            if (&(HT->table[i]) == target)
                printf("[%*s]  ", -1 * (width3 - 2), HT->table[i].key);
            else
                printf("%*s  ", -1 * width3, HT->table[i].key);
            printf("%p\n", HT->table[i].data);
        }
    }
}

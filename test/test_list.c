#include "list.h"
#include <stdio.h>
#include <assert.h>

void printList(list L, nodeptr target);

int main(int argc, char * argv[])
{
    list L;
    nodeptr target;
    int ret, option, data;

    L = createList();
    assert(L != NULL);

    printList(L, NULL);
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

        printf(">> Data: ");
        ret = scanf("%d", &data);
        assert(ret == 1);

        switch (option)
        {
        case 0:
            ret = insertElement(L, data);
            assert(ret == 0);
            target = NULL;
            break;
        case 1:
            target = findElement(L, data);
            if (target == NULL)
            {
                printf("   not found\n");
                goto noprint;
            }
            break;
        case 2:
            ret = deleteElement(L, data);
            if (ret == -1)
            {
                printf("   no deletion\n");
                goto noprint;
            }
            target = NULL;
            break;
        default:
            break;
        }

        printList(L, target);
noprint:
        printf("\n");
    }

    destroyList(L);

    return 0;
}

void printList(list L, nodeptr target)
{
    nodeptr this;

    this = L->next;

    printf("dummy head -> ");
    while (this != NULL)
    {
        if (this == target)
            printf("[%d] -> ", this->data);
        else
            printf("%d -> ", this->data);
        this = this->next;
    }
    printf("null\n");
}

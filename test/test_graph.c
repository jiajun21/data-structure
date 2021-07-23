#include "graph.h"
#include <stdio.h>
#include <assert.h>

void printGraph(graph G, unsigned int Vout, unsigned int Vin);

int main(int argc, char * argv[])
{
    graph G;
    unsigned int Vnum, Vout, Vin;
    int ret, option, weight;

    printf(">> graph vertex number: ");
    ret = scanf("%u", &Vnum);
    assert(ret == 1);
    printf("\n");

    G = createGraph(Vnum);
    assert(G != NULL);

    printGraph(G, 0, 0);
    printf("\n");

    while (1)
    {
        printf(">> 0. insert\n");
        printf("   1. query\n");
        printf("   2. delete\n");
        printf("   3. quit\n");
        printf(">> ");
        ret = scanf("%d", &option);
        assert(ret == 1);

        if (option == 3)
            break;

        printf(">> Vout Vin: ");
        ret = scanf("%d", &Vout);
        assert(ret == 1);
        ret = scanf("%d", &Vin);
        assert(ret == 1);

        if (option == 0)
        {
            printf("   Weight: ");
            ret = scanf("%d", &weight);
            assert(ret == 1);
        }

        switch (option)
        {
        case 0:
            ret = insertEdge(G, Vout, Vin, weight);
            assert(ret != -1);
            break;
        case 1:
            weight = queryEdge(G, Vout, Vin);
            if (weight == INT_NULL)
                printf("   edge does not exist\n");
            else
                printf("   <%d, %d> = %d\n", Vout, Vin, weight);
            break;
        case 2:
            ret = deleteEdge(G, Vout, Vin);
            if (ret == -1)
                printf("   edge does not exist\n");
            break;
        default:
            break;
        }

        printGraph(G, Vout, Vin);
        printf("\n");
    }

    destroyGraph(G);

    return 0;
}

static int _getItemWidth(int n)
{
    int ret;

    ret = 1;

    if (n < 0)
    {
        ret += 1;
        n = -1 * n;
    }

    while (n > 9)
    {
        n /= 10;
        ret += 1;
    }

    return ret;
}

void printGraph(graph G, unsigned int Vout, unsigned int Vin)
{
    nodeptr this;
    int width, ret;

    width = 0;

    for (int i = 0; i < G->Vnum; i++)
    {
        ret = _getItemWidth(i + 1);
        if (ret > width)
            width = ret;
        this = G->Edge[i];
        while (this != NULL)
        {
            ret = _getItemWidth(this->weight);
            if (ret > width)
                width = ret;
            this = this->next;
        }
    }

    if (Vout != 0 || Vin != 0)
        width += 2;

    if (G->Vnum > 0)
    {
        printf("%*c", width + 1, ' ');
        for (int i = 0; i < G->Vnum - 1; i++)
        {
            printf("%*d ", -1 * width, i + 1);
        }
        printf("%*d\n", -1 * width, G->Vnum);
    }
    for (int i = 0; i < G->Vnum; i++)
    {
        this = G->Edge[i];
        printf("%*d ", -1 * width, i + 1);
        for (int j = 0; j < G->Vnum - 1; j++)
        {
            if (this != NULL)
            {
                if (this->Vindex - 1 == j)
                {
                    if (Vout - 1 == i && Vin - 1 == j)
                        printf("[%*d] ", -1 * (width - 2), this->weight);
                    else
                        printf("%*d ", -1 * width, this->weight);
                    this = this->next;
                }
                else
                {
                    assert(this->Vindex - 1 > j);
                    printf("%*c ", -1 * width, '#');
                }
            }
            else
                printf("%*c ", -1 * width, '#');
        }
        if (this != NULL)
        {
            assert(this->Vindex == G->Vnum);
            if (Vout - 1 == i && Vin == G->Vnum)
                printf("[%*d]\n", -1 * (width - 2), this->weight);
            else
                printf("%*d\n", -1 * width, this->weight);
        }
        else
            printf("%*c\n", -1 * width, '#');
    }
}

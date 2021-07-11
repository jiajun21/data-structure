/**
 * implementation:
 * 0. adjacency list, each list is ordered
 * 1. Vindex starts from 1
 * 2. graph size can auto increase when insert
 * 3. insert becomes update when <Vout, Vin> exists
 */

#include "graph.h"
#include <stdlib.h>

static int _expandGraph(graph G, unsigned int Vnum)
{
    unsigned int old_Vnum;
    nodelist * old_Edge;

    old_Vnum = G->Vnum;
    old_Edge = G->Edge;
    G->Vnum = Vnum;
    G->Edge = (nodelist *)malloc(sizeof(nodelist) * G->Vnum);
    if (G->Edge == NULL)
    {
        G->Vnum = old_Vnum;
        G->Edge = old_Edge;
        return -1;
    }

    for (int i = 0; i < old_Vnum; i++)
        G->Edge[i] = old_Edge[i];

    for (int i = old_Vnum; i < G->Vnum; i++)
        G->Edge[i] = NULL;

    free(old_Edge);

    return 0;
}

graph createGraph(unsigned int Vnum)
{
    graph G;

    G = (graph)malloc(sizeof(struct graph_record));
    if (G != NULL)
    {
        G->Vnum = Vnum;
        G->Edge = (nodelist *)malloc(sizeof(nodelist) * G->Vnum);
        if (G->Edge == NULL)
        {
            free(G);
            G = NULL;
        }
        else
        {
            for (int i = 0; i < G->Vnum; i++)
                G->Edge[i] = NULL;
        }
    }

    return G;
}

int insertEdge(graph G, unsigned int Vout, unsigned int Vin, int weight)
{
    int ret;
    unsigned int max;
    nodeptr prev, this, new;

    if (Vout == 0 || Vin == 0)
        return -1;

    max = (Vout > Vin) ? Vout : Vin;
    if (max > G->Vnum)
    {
        ret = _expandGraph(G, max);
        if (ret == -1)
            return -1;
    }

    prev = NULL;
    this = G->Edge[Vout - 1];

    while (this != NULL)
    {
        if (this->Vindex == Vin)
        {
            this->weight = weight;
            return 0;
        }
        else if (this->Vindex > Vin)
            break;
        prev = this;
        this = this->next;
    }

    new = (nodeptr)malloc(sizeof(struct node));
    if (new == NULL)
        return -1;
    new->Vindex = Vin;
    new->weight = weight;
    new->next = this;

    if (prev == NULL)
        G->Edge[Vout - 1] = new;
    else
        prev->next = new;

    return 0;
}

int queryEdge(graph G, unsigned int Vout, unsigned int Vin)
{
    nodeptr this;

    if (Vout > G->Vnum || Vin > G->Vnum)
        return INT_NULL;
    if (Vout == 0 || Vin == 0)
        return INT_NULL;

    this = G->Edge[Vout - 1];

    while (this != NULL)
    {
        if (this->Vindex == Vin)
            return this->weight;
        else if (this->Vindex > Vin)
            break;
        this = this->next;
    }

    return INT_NULL;
}

int deleteEdge(graph G, unsigned int Vout, unsigned int Vin)
{
    nodeptr prev, this;

    if (Vout > G->Vnum || Vin > G->Vnum)
        return -1;
    if (Vout == 0 || Vin == 0)
        return -1;

    prev = NULL;
    this = G->Edge[Vout - 1];

    while (this != NULL)
    {
        if (this->Vindex == Vin)
        {
            if (prev == NULL)
                G->Edge[Vout - 1] = this->next;
            else
                prev->next = this->next;
            free(this);
            return 0;
        }
        else if (this->Vindex > Vin)
            return -1;
        prev = this;
        this = this->next;
    }

    return -1;
}

void destroyGraph(graph G)
{
    nodeptr this;

    for (int i = 0; i < G->Vnum; i++)
    {
        while (G->Edge[i] != NULL)
        {
            this = G->Edge[i];
            G->Edge[i] = this->next;
            free(this);
        }
    }
    free(G->Edge);
    free(G);
}

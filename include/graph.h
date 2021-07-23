#ifndef _GRAPH_H_
#define _GRAPH_H_

#define INT_NULL -1

typedef struct node * nodeptr;
typedef struct node * nodelist;
typedef struct graph_record * graph;

struct node
{
    unsigned int Vindex;
    int weight;
    nodeptr next;
};

struct graph_record
{
    unsigned int Vnum;
    nodelist * Edge;
};

graph createGraph(unsigned int Vnum);
int insertEdge(graph G, unsigned int Vout, unsigned int Vin, int weight);
int queryEdge(graph G, unsigned int Vout, unsigned int Vin);
int deleteEdge(graph G, unsigned int Vout, unsigned int Vin);
void destroyGraph(graph G);

#endif

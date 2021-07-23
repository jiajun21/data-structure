#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#undef DEBUG
#define THRESHOLD 0.5

typedef struct node * nodeptr;
typedef struct node * nodelist;
typedef struct hashtable_record * hashtable;

enum state {empty, inserted, deleted};

struct node
{
    enum state s;
    char * key;
    void * data;
};

struct hashtable_record
{
    unsigned int size;
    unsigned int stock;
    nodelist table;
};

hashtable createHashtable(unsigned int size);
int insertElement(hashtable HT, char * key, void * data);
nodeptr findElement(hashtable HT, char * key);
int deleteElement(hashtable HT, char * key);
void destroyHashtable(hashtable HT);

#endif

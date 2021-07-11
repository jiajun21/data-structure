/**
 * implementation:
 * 0. use quadratic probing
 * 1. insert mallocs new key
 * 2. insert becomes update when key is duplicate
 */

#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

static int _hash(hashtable HT, char * key)
{
#ifdef DEBUG
    return 0;
#else
    /* BKDR Hash Function */
    int hash;
    char * this;

    hash = 0;
    this = key;

    while (*this)
    {
        hash = hash * 131 + (*this);
        this ++;
    }

    return (hash & 0x7FFFFFFF) % HT->size;
#endif /* DEBUG */
}

static int _isprime(unsigned int n)
{
    if (n <= 1)
        return 0;
    else if (n <= 3)
        return 1;
    else
    {
        for (unsigned int i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
                return 0;
        }
    }

    return 1;
}

static unsigned int _makeprime(unsigned int n)
{
    /* "if hashtable's size is a prime number of the form 4k+3,
       then the quadratic probing can probe the entire hashtable" */

    n = n + (3 - n % 4);
    while (!_isprime(n))
        n += 4;

    return n;
}

/**
 * if key exists, return key's index
 * if key does not exist, return index which key can be inserted
 *    either a deleted position, or an empty position
 */
static int _findIndex(hashtable HT, char * key)
{
    int index, delta, probe, diretion;
    int first_delete_index, first_flag;

    index = _hash(HT, key);
    delta = 0;
    probe = index;
    diretion = 1;
    first_delete_index = index;
    first_flag = 1;

    while (HT->table[probe].s != empty)
    {
        if (HT->table[probe].s == inserted)
        {
            if (strcmp(key, HT->table[probe].key) == 0)
                break;
        }
        else /* HT->table[probe].s == deleted */
        {
            if (first_flag)
            {
                first_flag = 0;
                first_delete_index = probe;
            }
        }
        if (diretion == 1)
        {
            diretion = -1;
            delta ++;
            probe = (index + delta * delta) % HT->size;
        }
        else /* diretion == -1 */
        {
            diretion = 1;
            probe = index - delta * delta;
            while (probe < 0)
                probe += HT->size;
        }
    }

    if (HT->table[probe].s == empty && !first_flag)
        return first_delete_index;

    return probe;
}

static int _expandHashtable(hashtable HT)
{
    nodelist old_table;
    unsigned int old_size;
    int index;

    old_size = HT->size;
    old_table = HT->table;
    HT->size = _makeprime(old_size * 2);
    HT->table = (nodelist)malloc(sizeof(struct node) * HT->size);
    if (HT->table == NULL)
    {
        HT->size = old_size;
        HT->table = old_table;
        return -1;
    }
    for (int i = 0; i < HT->size; i++)
    {
        HT->table[i].s = empty;
        HT->table[i].key = NULL;
        HT->table[i].data = NULL;
    }

    for (int i = 0; i < old_size; i++)
    {
        if (old_table[i].s == inserted)
        {
            index = _findIndex(HT, old_table[i].key);
            HT->table[index].s = inserted;
            HT->table[index].key = old_table[i].key;
            HT->table[index].data = old_table[i].data;
        }
    }

    free(old_table);

    return 0;
}

hashtable createHashtable(unsigned int size)
{
    hashtable HT;

    HT = (hashtable)malloc(sizeof(struct hashtable_record));
    if (HT != NULL)
    {
        HT->size = _makeprime(size);
        HT->stock = 0;
        HT->table = (nodelist)malloc(sizeof(struct node) * HT->size);
        if (HT->table == NULL)
        {
            free(HT);
            HT = NULL;
        }
        else
        {
            for (int i = 0; i < HT->size; i++)
            {
                HT->table[i].s = empty;
                HT->table[i].key = NULL;
                HT->table[i].data = NULL;
            }
        }
    }

    return HT;
}

int insertElement(hashtable HT, char * key, void * data)
{
    int ret, index;
    char * new;

    index = _findIndex(HT, key);

    if (HT->table[index].s == inserted)
    {
        HT->table[index].data = data;
        return 0;
    }

    if ((double)(HT->stock + 1) > HT->size * THRESHOLD)
    {
        ret = _expandHashtable(HT);
        if (ret == -1)
            return -1;
    }

    index = _findIndex(HT, key);

    new = (char *)malloc(sizeof(char) * (strlen(key) + 1));
    if (new == NULL)
        return -1;
    strcpy(new, key);
    HT->table[index].s = inserted;
    HT->table[index].key = new;
    HT->table[index].data = data;
    (HT->stock)++;

    return 0;
}

nodeptr findElement(hashtable HT, char * key)
{
    int index;

    index = _findIndex(HT, key);

    if (HT->table[index].s != inserted)
        return NULL;

    return &(HT->table[index]);
}

int deleteElement(hashtable HT, char * key)
{
    int index;

    index = _findIndex(HT, key);

    if (HT->table[index].s != inserted)
        return -1;

    free(HT->table[index].key);
    HT->table[index].s = deleted;
    HT->table[index].key = NULL;
    HT->table[index].data = NULL;
    (HT->stock)--;

    return 0;
}

void destroyHashtable(hashtable HT)
{
    for (int i = 0; i < HT->size; i++)
    {
        if (HT->table[i].s == inserted)
            free(HT->table[i].key);
    }
    free(HT->table);
    free(HT);
}

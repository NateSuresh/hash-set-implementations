//Nathanael Suresh CSEN 12 Lab 4

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "set.h"
#include <stdbool.h>
#include "list.h"

#define AVG_LEN 20

// The set structure holds metadata and an array of buckets (lists)
typedef struct set {
    int count;
    int length;
    LIST **data;
    int (*compare)();
    unsigned (*hash)();
} SET;

// Creates a new set with allocated space and initializes each bucket
// time complexity: O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
    int i;
    SET *p;
    p = malloc(sizeof(SET));
    assert(p != NULL);
    p->count = 0;
    p->length = maxElts/AVG_LEN;
    p->data = malloc(sizeof(void*)*p->length);
    assert(p->data!= NULL);
    p->compare = compare;
    p->hash = hash;
    for(i=0;i<p->length;i++)
    {
        p->data[i] = createList(compare);
    }
    return p;
}

// Determines the bucket index using the hash function
// typically runs in constant time
// in the worst case, it may degrade significantly
static int search(SET *sp, void *elt, bool *found)
{
    assert(sp != NULL);
    assert(elt != NULL);
    int i;
    i = (*sp->hash)(elt) % sp->length;
    if(findItem(sp->data[i], elt) != NULL)
    {
        *found = true;                                          
        return i;
    }
    else
    {
        *found = false;
        return i;
    }
}

// Inserts a new element into the set if it's not already present
// time complexity: O(n)
void addElement(SET *sp, void *elt)
{
    bool found = false;
    assert(elt != NULL);
    assert(sp != NULL);
    int element = search(sp, elt, &found);
    if(!found)
    {
        addLast(sp->data[element], elt);
        sp->count++;
    }
    return;
}

// Returns how many items are currently stored in the set
// time complexity: O(1)
int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
}

// Deletes a specific element from the set if it exists
// time complexity: O(n)
void removeElement(SET *sp, void *elt)
{
    bool found = false;
    assert(sp != NULL);
    assert(elt != NULL);
    int element = search(sp, elt, &found);
    if(!found)
        return;
    removeItem(sp->data[element],elt);
    sp->count--;
    return;
}

// Searches for and returns the element if found
// time complexity: O(n)
void *findElement(SET *sp, void *elt)
{
    bool found = false;
    assert(sp != NULL);
    assert(elt != NULL);
    int element = search(sp, elt, &found);
    if(!found)
        return NULL;
    return findItem(sp->data[element],elt);
}

// Collects all elements from all buckets into a single array
// time complexity: O(n)
void *getElements(SET *sp)
{
    int i,j,counter = 0;
    assert(sp != NULL);
    void **temp;
    void **list;
    temp = malloc(sizeof(void *) * sp->count);
    assert(temp != NULL);
    for (i = 0; i < sp->length; i++) {
    int num = numItems(sp->data[i]);
    list = getItems(sp->data[i]);
    for (j = 0; j < num; j++) {
        temp[counter++] = list[j];
    }
    free(list);  // free the array returned by getItems
}

    return temp;
}

// Frees all memory used by the set and its buckets
// time complexity: O(n)
void destroySet(SET *sp)
{
    int i;
    assert(sp != NULL);
    for (i=0; i<sp->length; i++)
    {
        destroyList(sp->data[i]);
    }
    free(sp->data);
    free(sp);
    return;
}

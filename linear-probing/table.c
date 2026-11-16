/*
 * File:        table.c
 *
 * Copyright:   2021, Darren C. Atkinson
 *
 * Description: Generic set implementation using a hash table with
 *              linear probing.
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <stdbool.h>
# include "set.h"

# define EMPTY   0
# define FILLED  1
# define DELETED 2

struct set {
    int count;
    int length;
    void **data;
    char *flags;
    int (*compare)();
    unsigned (*hash)();
};

static int search(SET *sp, void *elt, bool *found)
{
    int available, i, locn, start;

    available = -1;
    start = (*sp->hash)(elt) % sp->length;

    for (i = 0; i < sp->length; i ++) {
        locn = (start + i) % sp->length;

        if (sp->flags[locn] == EMPTY) {
            *found = false;
            return available != -1 ? available : locn;
        } else if (sp->flags[locn] == DELETED) {
            if (available == -1)
                available = locn;
        } else if ((*sp->compare)(sp->data[locn], elt) == 0) {
            *found = true;
            return locn;
        }
    }

    *found = false;
    return available;
}

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)())
{
    int i;
    SET *sp;

    assert(compare != NULL && hash != NULL);

    sp = malloc(sizeof(SET));
    assert(sp != NULL);

    sp->data = malloc(sizeof(char *) * maxElts);
    assert(sp->data != NULL);

    sp->flags = malloc(sizeof(char) * maxElts);
    assert(sp->flags != NULL);

    sp->compare = compare;
    sp->hash = hash;
    sp->length = maxElts;
    sp->count = 0;

    for (i = 0; i < maxElts; i ++)
        sp->flags[i] = EMPTY;

    return sp;
}

void destroySet(SET *sp)
{
    assert(sp != NULL);
    free(sp->flags);
    free(sp->data);
    free(sp);
}

int numElements(SET *sp)
{
    assert(sp != NULL);
    return sp->count;
}

void addElement(SET *sp, void *elt)
{
    int locn;
    bool found;

    assert(sp != NULL && elt != NULL);
    locn = search(sp, elt, &found);

    if (!found) {
        assert(sp->count < sp->length);
        sp->data[locn] = elt;
        sp->flags[locn] = FILLED;
        sp->count ++;
    }
}

void removeElement(SET *sp, void *elt)
{
    int locn;
    bool found;

    assert(sp != NULL && elt != NULL);
    locn = search(sp, elt, &found);

    if (found) {
        sp->flags[locn] = DELETED;
        sp->count --;
    }
}

void *findElement(SET *sp, void *elt)
{
    int locn;
    bool found;

    assert(sp != NULL && elt != NULL);
    locn = search(sp, elt, &found);
    return found ? sp->data[locn] : NULL;
}

void *getElements(SET *sp)
{
    int i, j;
    void **elts;

    assert(sp != NULL);

    elts = malloc(sizeof(void *) * sp->count);
    assert(elts != NULL);

    for (i = 0, j = 0; i < sp->length; i ++)
        if (sp->flags[i] == FILLED)
            elts[j ++] = sp->data[i];

    return elts;
}

// COEN 12 Lab 2
// This code provides an implementation of a basic string collection using a set data structure.

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "set.h"

// Structure to hold the string set: current size, max capacity, and the string array
typedef struct set {
    int size;       // number of current elements
    int capacity;   // max number of elements
    char **items;   // array of string pointers
} SET;

// Creates and returns a new set with space for up to maxSize strings
// Time complexity: O(1)
SET *createSet(int maxSize)
{
    SET *s;
    s = malloc(sizeof(SET));
    assert(s != NULL);
    s->size = 0;
    s->capacity = maxSize;
    s->items = malloc(sizeof(char*) * maxSize);
    assert(s->items != NULL);
    return s;
}

// Internal function to find index of a string in the set
// Returns index if found, else -1
// Time complexity: O(n)
static int locate(SET *s, char *str)
{
    for (int i = 0; i < s->size; i++) {
        if (strcmp(s->items[i], str) == 0)
            return i;
    }
    return -1;
}

// Adds a new string to the set if it's not already present
// Time complexity: O(n)
void addElement(SET *s, char *str)
{
    assert(s != NULL);
    if (s->size >= s->capacity || locate(s, str) != -1)
        return;
    s->items[s->size] = strdup(str);
    s->size++;
}

// Returns how many elements are in the set
// Time complexity: O(1)
int numElements(SET *s)
{
    assert(s != NULL);
    return s->size;
}

// Removes a string from the set if it exists
// Time complexity: O(n)
void removeElement(SET *s, char *str)
{
    assert(s != NULL);
    int idx = locate(s, str);
    if (idx == -1)
        return;
    free(s->items[idx]);
    s->items[idx] = s->items[s->size - 1];
    s->items[s->size - 1] = NULL;
    s->size--;
}

// Returns a pointer to the matching string if found, otherwise NULL
// Time complexity: O(n)
char *findElement(SET *s, char *str)
{
    assert(s != NULL);
    int idx = locate(s, str);
    if (idx == -1)
        return NULL;
    return s->items[idx];
}

// Returns a shallow copy of the array of strings in the set
// Time complexity: O(1)
char **getElements(SET *s)
{
    assert(s != NULL);
    char **copy = malloc(sizeof(char*) * s->size);
    assert(copy != NULL);
    memcpy(copy, s->items, sizeof(char*) * s->size);
    return copy;
}

// Frees all memory used by the set
// Time complexity: O(n)
void destroySet(SET *s)
{
    assert(s != NULL);
    for (int i = 0; i < s->size; i++) {
        free(s->items[i]);
    }
    free(s->items);
    free(s);
}

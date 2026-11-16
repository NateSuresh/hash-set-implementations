// COEN 12 Lab 2
// Provides a string set data structure using sorted array and binary search

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "set.h"

// Structure for the string set, storing count, capacity, and string array
typedef struct set {
    int size;       // number of current elements
    int capacity;   // max number of elements allowed
    char **items;   // array of string pointers
} SET;

// Creates a new set that can store up to maxItems strings
// Time complexity: O(1)
SET *createSet(int maxItems)
{
    SET *s = malloc(sizeof(SET));
    assert(s != NULL);
    s->size = 0;
    s->capacity = maxItems;
    s->items = malloc(sizeof(char*) * maxItems);
    assert(s->items != NULL);
    return s;
}

// Helper function that searches for a string using binary search
// Sets *exists to true if found, otherwise false
// Time complexity: O(log n)
static int binarySearch(SET *s, char *str, bool *exists)
{
    assert(s != NULL && str != NULL);
    int low = 0, high = s->size - 1, mid;

    while (low <= high) {
        mid = (low + high) / 2;
        int cmp = strcmp(str, s->items[mid]);
        if (cmp < 0)
            high = mid - 1;
        else if (cmp > 0)
            low = mid + 1;
        else {
            *exists = true;
            return mid;
        }
    }

    *exists = false;
    return low;
}

// Inserts a string into the set if it doesn't already exist
// Time complexity: O(n)
void addElement(SET *s, char *str)
{
    assert(s != NULL && str != NULL);
    bool exists;
    int index = binarySearch(s, str, &exists);
    if (exists || s->size == s->capacity)
        return;

    for (int i = s->size; i > index; i--)
        s->items[i] = s->items[i - 1];

    s->items[index] = strdup(str);
    s->size++;
}

// Returns the total number of elements currently in the set
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
    assert(s != NULL && str != NULL);
    bool exists;
    int index = binarySearch(s, str, &exists);
    if (!exists)
        return;

    free(s->items[index]);
    for (int i = index + 1; i < s->size; i++)
        s->items[i - 1] = s->items[i];

    s->size--;
}

// Returns the matching string from the set or NULL if not found
// Time complexity: O(log n)
char *findElement(SET *s, char *str)
{
    assert(s != NULL && str != NULL);
    bool exists;
    int index = binarySearch(s, str, &exists);
    return exists ? s->items[index] : NULL;
}

// Returns a deep copy of the strings in the set
// Time complexity: O(n)
char **getElements(SET *s)
{
    assert(s != NULL);
    char **copy = malloc(sizeof(char*) * s->size);
    assert(copy != NULL);

    for (int i = 0; i < s->size; i++)
        copy[i] = strdup(s->items[i]);

    return copy;
}

// Frees all memory associated with the set
// Time complexity: O(n)
void destroySet(SET *s)
{
    assert(s != NULL);
    for (int i = 0; i < s->size; i++)
        free(s->items[i]);

    free(s->items);
    free(s);
}

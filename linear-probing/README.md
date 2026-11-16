# Linear Probing Hash Set

This version stores items in a hash table and uses linear probing to handle collisions.

A collision happens when two items try to use the same spot in the table.

## Features

- Add items
- Remove items
- Search for items
- Use a hash function
- Handle collisions with linear probing
- Track empty, filled, and deleted spots
- Return all stored items

## How It Works

The hash function chooses where an item should go in the table.

If that spot is already being used, the program checks the next spot until it finds an open one.

If an item is deleted, that spot is marked as deleted instead of completely empty so searching still works correctly.

Searching, adding, and deleting are usually close to O(1) on average.

## Files

- `table.c` - Hash table and linear probing implementation
- `unique.c` - Tests the set using words from text files
- `set.h` - Set function declarations

## What I Learned

This version helped me understand hash tables, hash functions, collisions, linear probing, and how searching can be faster with hashing.

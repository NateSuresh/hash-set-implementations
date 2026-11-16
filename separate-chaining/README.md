# Separate Chaining Hash Set

This version stores items in a hash table and uses linked lists to handle collisions.

Each spot in the hash table has its own linked list.

## Features

- Add items
- Remove items
- Search for items
- Use a hash function
- Handle collisions with linked lists
- Store multiple items in the same bucket
- Return all stored items

## How It Works

The hash function decides which bucket an item should go into.

Each bucket is a linked list.

If two items go to the same bucket, both items can be stored in that linked list.

This is different from linear probing because the program does not need to keep checking the next spots in the table.

## Files

- `set.c` - Hash set using separate chaining
- `list.c` - Linked list implementation
- `list.h` - Linked list function declarations
- `unique.c` - Tests the set using words from text files
- `set.h` - Set function declarations

## What I Learned

This version helped me understand separate chaining, linked lists, hash tables, pointers, and how different data structures can work together.

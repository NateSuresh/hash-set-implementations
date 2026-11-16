# Unsorted Array Set

This version stores unique strings in an unsorted array.

The program checks the array one item at a time when it needs to find something.

## Features

- Add unique strings
- Remove strings
- Search for strings
- Return all stored strings
- Track the number of items

## How It Works

The set stores string pointers inside an array.

When a new string is added, the program first checks if it is already in the set.

Because the array is not sorted, searching can take O(n) time.

## Files

- `unsorted.c` - Unsorted array set implementation
- `unique.c` - Tests the set using words from text files
- `set.h` - Set function declarations

## What I Learned

This version helped me understand basic set operations, arrays, dynamic memory, and linear search.

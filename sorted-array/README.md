# Sorted Array Set

This version stores unique strings in a sorted array.

Because the array stays sorted, the program can use binary search to find items faster.

## Features

- Add unique strings
- Keep strings sorted
- Remove strings
- Search using binary search
- Return all stored strings
- Track the number of items

## How It Works

When a new string is added, the program uses binary search to find where it should go.

The other items are moved over to make space for the new string.

Searching is faster than the unsorted version because binary search takes O(log n) time.

Adding and deleting can still take O(n) because items may need to be moved.

## Files

- `sorted.c` - Sorted array set implementation
- `unique.c` - Tests the set using words from text files
- `set.h` - Set function declarations

## What I Learned

This version helped me understand binary search and the tradeoff between faster searching and the extra work needed to keep an array sorted.

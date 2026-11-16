# Hash Set Implementations

This project shows different ways to build a set data structure in C.

A set stores unique items, so the same item is not added more than once.

I made different versions to see how the choice of data structure changes how fast searching, adding, and deleting can be.

## Implementations

### Unsorted Array

This version stores strings in a normal unsorted array.

To find an item, the program may have to check each item one by one.

### Sorted Array

This version keeps the array sorted.

Because the data is sorted, the program can use binary search to find items faster.

### Linear Probing

This version uses a hash table.

If two items try to use the same spot, the program checks the next open spot until it finds one.

### Separate Chaining

This version also uses a hash table, but collisions are handled with linked lists.

Each spot in the hash table points to a list that can hold multiple items.

## Project Structure

```text
hash-set-implementations/
├── unsorted-array/
│   ├── unsorted.c
│   ├── unique.c
│   ├── set.h
│   └── README.md
│
├── sorted-array/
│   ├── sorted.c
│   ├── unique.c
│   ├── set.h
│   └── README.md
│
├── linear-probing/
│   ├── table.c
│   ├── unique.c
│   ├── set.h
│   └── README.md
│
├── separate-chaining/
│   ├── set.c
│   ├── list.c
│   ├── list.h
│   ├── unique.c
│   ├── set.h
│   └── README.md
│
├── report.txt
├── README.md
└── .gitignore
```

## Technologies and Concepts

- C
- Arrays
- Binary Search
- Hash Tables
- Linear Probing
- Separate Chaining
- Linked Lists
- Dynamic Memory
- Pointers
- Time Complexity

## What I Learned

This project helped me understand that the same problem can be solved in different ways.

The unsorted array is simple, but searching can be slow.

The sorted array makes searching faster with binary search.

The hash table versions make searching, adding, and deleting faster on average.

I also learned two different ways to handle hash collisions: linear probing and separate chaining.

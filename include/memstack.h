// Memstack, a small utility written by khhs
// Name has 99% already been used a hundred times before
// But please do not remove this comment if you plan to use it.

// Header file

#ifndef MC_MEMSTACK_H
#define MC_MEMSTACK_H

#include <stdlib.h>
#include <stdio.h>

// C macro to improve readability when using the library.
// Example:
// Before: msfree(NULL);  // Does not explicitly show global is being freed
// After: msfree(GLOBAL_MEMSTACK);  // Does show global is being freed
// It isn't necessary to use this however, and using NULL will also work.
#define GLOBAL_MEMSTACK NULL

// Linked list node.
// Stores a ptr to the memory allocated and the next element in the linked list.
// If *next* is NULL then that node is the last node in the linked list.
typedef struct memstack_chain_ptr_t{
    void* ptr;  // Pointer to the memory allocated
    struct memstack_chain_ptr_t* next;  // Pointer to next node
} memstack_chain_ptr;

// Memstack structure.
// Stores the linked list for all of our allocations.
typedef struct memstack_t {
    memstack_chain_ptr* last;  // Stores last element
    memstack_chain_ptr* first;  // Stores first element
} memstack;

extern void msinit(); // Initializes a global memstack, that can be accessed by passing in "NULL" as storage in the other funcs
extern memstack* msnew();  // Creates a new memstack
extern void* msalloc(memstack* storage, int size);  // Allocate onto memstack and return pointer
extern void msfree(memstack* storage);  // Free all of memstack
extern void msclear(memstack* storage);  // Frees allocations but doesn't delete the memstack


#endif
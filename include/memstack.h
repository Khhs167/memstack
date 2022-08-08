// Memstack, a small utility written by khhs
// Name has 99% already been used a hundred times before
// But please do not remove this comment if you plan to use it.

// Header file

#ifndef MC_MEMSTACK_H
#define MC_MEMSTACK_H

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

extern memstack* new_memstack();  // Creates a new memstack
extern void* msalloc(memstack* storage, int size);  // Allocate onto memstack and return pointer
extern void msfree(memstack* storage);  // Free all of memstack


#endif
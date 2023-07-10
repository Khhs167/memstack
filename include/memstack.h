// Memstack, a small utility written by khhs
// Name has 99% already been used a hundred times before
// But please do not remove this comment if you plan to use it.

// Header file

#include <stdio.h>

#ifndef __MC_MEMSTACK_H_
#define __MC_MEMSTACK_H_

// C macro to improve readability when using the library.
// Example:
// Before: msfree(NULL);  // Does not explicitly show global is being freed
// After: msfree(GLOBAL_MEMSTACK);  // Does show global is being freed
// It isn't necessary to use this however, and using NULL will also work.
#define GLOBAL_MEMSTACK ((memstack*)NULL)

#define MSTRUE (1==1)
#define MSFALSE (!MSTRUE)


// Certain compilers support destructors, which are pieces of code invoked at the end of a programs lifetime.
// Now, because this doesn't apply to all compilers, we have the MSCLEANUP definition.
// This is defined for GCC, clang, and ICC, since those all support destructors.
// The intended use-case is just so that you can know whether or not the global stack will be automatically
// cleaned on your system, provided you compile memstack and the program with THE SAME COMPILER.
#if defined(__GNUC__) || defined(__clang__) || defined(__INTEL_COMPILER)
#define MSCLEANUP
#else
#warning Memstack global cleanup is not available for your compiler, make sure you clean it up yourself
#endif

#ifndef MSCLEANUP
#define MSCLEAN { msfree(GLOBAL_MEMSTACK); }
#else
#define MSCLEAN { }
#endif

// Linked list node.
// Stores a ptr to the memory allocated and the next element in the linked list.
// If *next* is NULL then that node is the last node in the linked list.
typedef struct memstack_chain_ptr_t {
    void* ptr;  // Pointer to the memory allocated
    struct memstack_chain_ptr_t* next;  // Pointer to next node
    struct memstack_chain_ptr_t* previous;  // Pointer to previous node
} memstack_chain_ptr;

// Memstack structure.
// Stores the linked list for all of our allocations.
typedef struct {
    memstack_chain_ptr* last;  // Stores last element
    memstack_chain_ptr* first;  // Stores first element
    int length;
} memstack;

extern void msinit(); // Initializes a global memstack, that can be accessed by passing in "NULL" as storage in the other funcs
extern memstack* msnew();  // Creates a new memstack
extern void* msalloc(memstack* storage, int size);  // Allocate onto memstack and return pointer
extern void msfree(memstack* storage);  // Free all of memstack
extern void msclear(memstack* storage);  // Frees allocations but doesn't delete the memstack
extern void mspush(memstack* storage, void* ptr);  // Adds new memory into the memstack even if it hasn't been allocated with msalloc()
extern void* mspop(memstack* storage);  // Removes the last node from the memstack and returns the user allocated memory
extern void msrollback(memstack* storage, int rollback_count, int destructive);  // Removes a number of nodes from a memstack
extern void msdealloc(memstack* storage, void* ptr); // Deallocate a piece of memory and remove it from the stack
extern void msfprint(memstack* storage, FILE* stream);  // Displays all the nodes in the memstack for debugging uses
extern void msprint(memstack* storage);  // Displays all the nodes in the memstack for debugging uses

#endif /* __MC_MEMSTACK_H_ */

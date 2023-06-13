#include <memstack.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Running example \"msrollback\"!\n");

    // Creating the memstack.
    // See msnew.c example
    memstack* example_memstack = msnew();

    // Allocating memory through msalloc()
    // See msalloc.c example
    int* a = msalloc(example_memstack, sizeof(int));
    int* b = msalloc(example_memstack, sizeof(int));
    int* c = msalloc(example_memstack, sizeof(int));
    int* d = msalloc(example_memstack, sizeof(int));

    // msrollback can be used to remove, and destroy, multiple allocations from the memstack.
    // Below, we destroy "c" and "d", and remove "a" and "b".
    msrollback(example_memstack, 2, MSTRUE);  // Destroy last two nodes
    msrollback(example_memstack, 2, MSFALSE);  // Remove last two nodes

    // We have to handle "a", and "b", ourself.
    free(a);
    free(b);

    // Remember to call msfree()!
    // See msfree.c example
    msfree(example_memstack);
}

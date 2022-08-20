#include <memstack.h>
#include <stdio.h>

int main(void) {
    printf("Running example \"msclear\"!\n");

    // Creating the memstack.
    // See msnew.c example
    memstack* example_memstack = msnew();

    // Allocating memory through msalloc()
    // See msalloc.c example
    int* a = msalloc(example_memstack, sizeof(int));
    int* b = msalloc(example_memstack, sizeof(int));
    int* c = msalloc(example_memstack, sizeof(int));
    int* d = msalloc(example_memstack, sizeof(int));

    // Clearing the memstack allocations.
    // This clears all allocations that have been made on the memstack so far.
    // All the allocations above have now been freed.
    msclear(example_memstack);


    // Further allocations can be made because the memstack will still
    // exist after being cleared.
    // If you were to msfree() instead of msclear() this would segfault.
    int* e = msalloc(example_memstack, sizeof(int));
    int* f = msalloc(example_memstack, sizeof(int));


    // Remember to call msfree()!
    // See msfree.c example
    msfree(example_memstack);
}
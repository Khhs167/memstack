#include <memstack.h>
#include <stdio.h>

int main(void) {
    printf("Running example \"msalloc\"!\n");

    // Creating the memstack.
    // See msnew.c example
    memstack* example_memstack = msnew();

    // Allocating memory through msalloc()
    // msalloc() will log the allocation in the memstack.
    // The advantage of this is the ability to msfree() every allocation shown below at once.
    int* a = msalloc(example_memstack, sizeof(int));
    int* b = msalloc(example_memstack, sizeof(int));
    int* c = msalloc(example_memstack, sizeof(int));
    int* d = msalloc(example_memstack, sizeof(int));

    // We can still use the pointers as normal
    *a = 100;
    *b = 101;
    *c = 900;
    *d = -10;


    // Remember to call msfree()!
    // See msfree.c example
    msfree(example_memstack);  // Everything (a, b, c, d) will be freed
}
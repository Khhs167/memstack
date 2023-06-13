#include <memstack.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Running example \"mspop\"!\n");

    // Creating the memstack.
    // See msnew.c example
    memstack* example_memstack = msnew();

    // Allocating memory through malloc (cstdlib).
    // See msalloc.c example
    int* a = msalloc(example_memstack, sizeof(int));

    // Sometimes, we no longer want an allocation on the memstack.
    // We can remove the last allocation added to the memstack using mspop().
    a = mspop(example_memstack);

    // Now that we have removed "a" from the memstack we have to handle it ourselves.
    // This means if we no longer want to play with "a" we have to free it ourselves.
    free(a);

    // Remember to call msfree()!
    // See msfree.c example
    msfree(example_memstack);  // Everything (a, b, c, d) will be freed
}

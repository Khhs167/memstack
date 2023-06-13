#include <memstack.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Running example \"mspush\"!\n");

    // Creating the memstack.
    // See msnew.c example
    memstack* example_memstack = msnew();

    // Allocating memory through malloc (cstdlib).
    // Sometimes we want to allocate ourselves!
    int* a = malloc(sizeof(int));

    // We can still add "a" to the memstack
    // We do this by using mspush()
    // Sometimes, we don't have control over how our memory is allocated
    // but still want it to be on the memstack.
    mspush(example_memstack, a);

    // Remember to call msfree()!
    // See msfree.c example
    msfree(example_memstack);  // Everything (a, b, c, d) will be freed
}

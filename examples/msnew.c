#include <memstack.h>
#include <stdio.h>

int main(void) {
    printf("Running example \"msnew\"!\n");

    // Creating the memstack.
    // msnew() will allocate memory for the memstack itself.
    // This means we must use msfree() later.
    memstack* example_memstack = msnew();

    // We can access the memstack's properties.
    example_memstack->length;  // Gets the number of nodes in the memstack.
    example_memstack->first;  // Gets the first node in the memstack.
    example_memstack->last;  // Gets the last node in the memstack.

    // Using ->first and ->last is not advised.
    // Modifying either of these pointers could cause memstack to lose track of
    // every allocation you've made.

    // Forgetting to call msfree() will cause a memory leak.
    msfree(example_memstack);
}

#include <memstack.h>
#include <stdio.h>

int main(void) {
    printf("Running example \"msfree\"!\n");

    // Creating the memstack.
    // See msnew.c example
    memstack* example_memstack = msnew();


    // Forgetting to call msfree() will cause a memory leak.
    // msfree() must always be called after the initialisation of a memstack.
    // Even if a memstack has been cleared or is empty it still needs to go through msfree().
    // This is because the memstack itself is heap allocated not stack allocated.
    msfree(example_memstack);
}
#include <memstack.h>
#include <stdio.h>

int main(){

    printf("Creating global memstack!\n");
    msinit();

    int* ptr = (int*)msalloc(GLOBAL_MEMSTACK, sizeof(int));
    printf("ptr: %d\n", *ptr);
    printf("Setting ptr to 60\n");
    *ptr = 60;
    printf("ptr: %d\n", *ptr);
    
    printf("Done!\n");
    
    msfree(NULL);

    return 0;
}

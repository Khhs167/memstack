#include <memstack.h>
#include <stdlib.h>

int main(){

    msinit();

    int* test = msalloc(sizeof(int), NULL);

    msfree(NULL);

    return 0;
}
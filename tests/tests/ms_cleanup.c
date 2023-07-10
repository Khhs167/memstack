#include <memstack.h>
#include <stdio.h>

int main(){

    printf("Creating global memstack!\n");
    msinit();
    
    // Not the prettiest, but it "works"
    MSCLEAN

    return 0;
}

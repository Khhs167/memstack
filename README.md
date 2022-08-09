# memstack
A basic linked-list based tool for managing memory

## Installation
```
sudo make install
```
And to remove
```
sudo make uninstall
```

This library has 3 functions, `msnew`, `msalloc` and `msfree`.
When you want to create a memstack (for storing all allocations so they can later be freed at once), use the function `msnew()` which returns a `memstack` pointer. You can use `msalloc(memstack*, int)` to allocate new memory through the memstack, this function will return a pointer to the memory you've allocated. Once you're all ton with the memory, you can free it all at once using `msfree(memstack*)`!

## Compiling something
Just make sure you have the thing installed, and add `-lmemstack` to the gcc linking flags.

## Example program
```c
// example.c
// Compile with "gcc example.c -lmemstack -o example" and run with "./example"

#include <stdio.h>
#include <memstack.h>

void inc(int* v){
  *v = *v + 1;
}

int main(){
  memstack* ms = msnew(); // Create your own memstack!
  
  int* a = msalloc(ms, sizeof(int)); // Create an int pointer
  *a = 10; // Lets set it to 10
  printf("A: %i\n", *a); // Print the value(should give us "A: 10"
  inc(a); // Increase it
  printf("A: %i\n", *a); // Now it should give us "A: 11"
  
  msfree(ms); // Free it all. 
}
```

# memstack
A basic linked-list based tool for managing memory

## Installation

It can be installed via the AUR(`yay -S libmemstack-git` i.e) or via Makefile as shown below
```
sudo make install
```
And to remove(with makefile)
```
sudo make uninstall
```

This library has 4 functions, `msnew`, `msalloc`, `msfree` and the legacy function `msinit`.
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

## Legacy example
```c
// example.c
// Compile with "gcc example.c -lmemstack -o example" and run with "./example"

#include <stdio.h>
#include <memstack.h>
#include <stdlib.h>

void inc(int* v){
  *v = *v + 1;
}

int main(){
  msinit() // Create a global memstack
  // Note that unlike the above example, we pass NULL instead of a memstack, that accesses the global
  // Memstack.
  
  // As of the latest update, GLOBAL_MEMSTACK also works.
  
  int* a = msalloc(NULL, sizeof(int)); // Create an int pointer
  *a = 10; // Lets set it to 10
  printf("A: %i\n", *a); // Print the value(should give us "A: 10"
  inc(a); // Increase it
  printf("A: %i\n", *a); // Now it should give us "A: 11"
  
  msfree(GLOBAL_MEMSTACK); // Free it all using our GLOBAL_MEMSTACK macro because cool!
}
```

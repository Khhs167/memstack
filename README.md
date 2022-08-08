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

This library has 3 functions, `msinit`, `msalloc` and `msfree`.
At the top of the program, call `msinit()` this will setup everything for you, and at the end call `msfree()`, which will free all the allocated memory.
Memory allocation is like with libc, `msalloc(size)`, which will give you a void* to memory of `size` bytes.

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
  msinit(); // Init the lib
  
  int* a = msalloc(sizeof(int)); // Create an int pointer
  *a = 10; // Lets set it to 10
  printf("A: %i\n", *a); // Print the value(should give us "A: 10"
  inc(a); // Increase it
  printf("A: %i\n", *a); // Now it should give us "A: 11"
  
  msfree(); // Free it all. Library is now unusable until the next msinit()
}
```

# memstack
A basic linked-list based tool for managing memory

## Installation

### Build from source
To install with Makefile, first ensure you have `make` installed, clone the git repository, change into the projects directory and run the command shown below:
```
sudo make install
```
And to remove(with makefile)
```
sudo make uninstall
```

### AUR installation
The [AUR (Arch User Repository)](https://aur.archlinux.org/) is a community-driven repository for Arch Linux. 
The installation instructions below are only available to those to use the Arch Linux operating system.

To install memstack from the AUR you need the AUR link (https://aur.archlinux.org/libmemstack-git.git) from the [memstack AUR page](https://aur.archlinux.org/packages/libmemstack-git).
After copying, you'll need to clone, and build the library with `makepkg -si`
```
$ git clone 
$ cd libmemstack-git
$ makepkg -si
```
However, most people will use a [AUR client](https://wiki.archlinux.org/title/AUR_helpers) which handles everything for us:
```
$ yay -S libmemstack-git
```
*NOTE: this example uses yay*

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

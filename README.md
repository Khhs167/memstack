# memstack
A linked-list based, easy to use and well documented, C library for managing memory in your programs.

## Installation

### Build from source
To install with Makefile, first ensure you have `make` installed, clone the git repository, change into the projects directory and run the command `sudo make install`.
```
$ git clone https://github.com/Khhs167/memstack.git
$ cd memstack
$ sudo make install
```
To remove the library, ensure you are inside the repository's folder and uninstall with the following make command.
```
$ sudo make uninstall
```

### AUR installation
The [AUR (Arch User Repository)](https://aur.archlinux.org/) is a community-driven repository for Arch Linux. 
The installation instructions below are only available to those to use the Arch Linux operating system.

To install memstack from the AUR you need the AUR link (https://aur.archlinux.org/libmemstack-git.git) from the [memstack AUR page](https://aur.archlinux.org/packages/libmemstack-git).
After copying, you'll need to clone, and build the library with `makepkg -si`
```
$ git clone https://aur.archlinux.org/libmemstack-git.git
$ cd libmemstack-git
$ makepkg -si
```
However, most people will use a [AUR client](https://wiki.archlinux.org/title/AUR_helpers) which handles everything for us:
```
$ yay -S libmemstack-git
```
*NOTE: this example uses [yay](https://github.com/Jguer/yay)*

## Usage

### To compile using memstack
To compile a program with the memstack library use the `-lmemstack` compiler flag like shown below.
```sh 
$ gcc program.c -lmemstack
(or with clang)
$ clang program.c -lmemstack
```

### Creating a memstack
The memstack library has a type called `memstack*` used to keep track of allocations.
To create a memstack, you can use the function `msnew()` as shown below.
```c 
#include <memstack.h>

// Example C program using memstack
int main() {
    // We crate a new memstack using the function msnew()
    memstack* ms = msnew(); 
    // ... 
    msfree(ms);  // Free the memstack
    return 0;
}
```
It's important to note that `msfree(memstack*);` will free the entire memstack (including the memstack itself).
This means the memstack we define `ms` will no longer be usable after `msfree(ms)` is called.

### Memstack functions

#### memstack* msnew()
`msnew` (usage: `msnew()`) will return a memstack pointer that can be used in conjunction with other memstack functions to 
add allocations, deallocate, clear, and free more easily.
```c 
// Example of creating a new memstacking using msnew().
memstack* example_memstack = msnew();
```

#### void msfree(memstack*)
`msfree` (usage: `msfree(memstack*)`) will free all the allocations logged on a memstack and free the memstack passed into it.
It's recommended this function be called to free any initialised memstack at the end of the program.

```c 
// Example of creating (using msnew(), and freeing (using msfree()) a memstack.
memstack* example_memstack = msnew();  // Create memstack.
msfree(example_memstack);  // Destroy memstack.
```
Using `msfree` on a `memstack*` will deallocate the `memstack*` itself. 
This means trying to use a `memstack*` after it has been freed via `msfree` will cause undefined behaviour.

#### void* msalloc(memstack*, int)
`msalloc` (usage: `msalloc(memstack*, int)`) will allocate a given size and add it onto the given memstack.
`msalloc` will return a `void*` which can be used, manipulated, and eventually freed using `msfree`.

```c 
memstack* example_memstack = msnew();  // Create a new memstack for allocations.

// Example of allocating onto a memstack.
int* a = msalloc(example_memstack*, sizeof(int));
int* b = msalloc(example_memstack*, sizeof(int));
int* c = msalloc(example_memstack*, sizeof(int));

// Freeing the memstack.
msfree(example_memstack);
```

#### void msclear(memstack*)
`msclear` (usage: `msclear(memstack*)`) will free all the allocation on a memstack but will not destroy the memstack itself.
This function does a similar job to `msfree` but does not destroy the `memstack*` after.
This allows the `memstack*` to be used for further allocations even after freeing everything.

```c 
memstack* example_memstack = msnew();  // Create a new memstack for allocations.

// Example of allocating onto a memstack.
int* a = msalloc(example_memstack*, sizeof(int));

// Clearing the memstack.
msclear(example_memstack);  // a has been freed. Memstack is empty.

// Freeing the memstack.
// You must still clear the memstack itself so msfree still has to be called after msclear.
msfree(example_memstack);
```

#### void mspush(memstack*, void*)
`mspush` (usage: `mspush(memstack*, void*)`) allows you to add allocations to a `memstack*` without having to allocate using `msalloc`.
`mspush` will not allocate space, but instead can be used to add already allocated space to a `memstack*`.
This is useful for adding allocations which you may not have easy control over, such as when using a library.

```c 
memstack* example_memstack = msnew();  // Create a new memstack for allocations.

// Create an allocation (without msalloc)
int* a = malloc(sizeof(int));

// Add the allocation to the memstack
mspush(example_memstack, a);

// Freeing the memstack.
msfree(example_memstack);
```

#### void* mspop(memstack*)
`mspop` (usage: `mspop(memstack*)`) will remove the latest element of a give `memstack*` and return the element's allocated space.
This allows you to remove allocations from the `memstack*` and handle it yourself.
It's important to note that calling `mspop` will remove the allocation from the `memstack*`, and therefore the allocation will not be freed when `msfree` is called.

```c 
memstack* example_memstack = msnew();  // Create a new memstack for allocations.

// Example of allocating onto a memstack.
int* a = msalloc(example_memstack*, sizeof(int));

// Remove "a" from the memstack.
int* a = mspop(example_memstack);

// Freeing the memstack.
msfree(example_memstack);

// Since "a" is no longer being handled by the memstack, you must free it yourself. 
free(a);
```

#### void msrollback(memstack*, int, int)
`msrollback` (usage: `msrollback(memstack*, int, int)`) can be used to remove multiple elements from a `memstack*`.
`msrollback` will begin removing elements starting from the latest element, it will remove only the given number of elements, from the given `memstack*`.
Elements can be removed both "destructively" (i.e. the memory is cleared), or "non-destructively" (i.e. the memory is not cleared).
If the memory is not cleared, you, the programmer, must handle freeing the memory yourself.

An example of `msrollback` is shown below. 
For this example `TRUE` is defined as `1` and `FALSE` as 0.

```c 
memstack* example_memstack = msnew();  // Create a new memstack for allocations.

// Example of allocating onto a memstack.
int* a = msalloc(example_memstack*, sizeof(int));
int* b = msalloc(example_memstack*, sizeof(int));
int* c = msalloc(example_memstack*, sizeof(int));

// Remove two elements destructively.
msrollback(example_memstack, 2, TRUE);  // "b" and "c" are removed and freed!

// Remove one element non-destructively.
msrollback(example_memstack, 1, FALSE);  // "a" is removed (but not freed)!

// Freeing the memstack.
msfree(example_memstack);

// We must handle freeing "a" ourself because it doesn't belong to the memstack
free(a);
```

### Global memstack
The functions covered above are explained using a user created memstack (created through `msnew()`).
However, the library also has a global memstack internal to the library.
This allows for allocations to be made from anywhere in a codebase.

In order to start using the global memstack, the user must call the `msinit()` function.
This function does not return anything, and initialises the global memstack.

After initialising the global memstack, you can manipulate the memstack using the same functions explained above.
However, instead of using our user created memstack, you can pass in the macro `GLOBAL_MEMSTACK`.
The function called will know you're referring to the global memstack and manipulate this instead.

An example of using the global memstack is shown below.

```c 
#include <memstack.h>
#include <stdlib.h>

int main() {
    msinit();  // Initialise the global memstack.
    
    // Allocating onto global
    int* example1 = msalloc(GLOBAL_MEMSTACK, sizeof(int));
    
    // Clearing global
    msclear(GLOBAL_MEMSTACK);
    
    msfree(GLOBAL_MEMSTACK);  // Free global memstack.
}
```
*NOTE: `GLOBAL_MEMSTACK` is a macro for `NULL`. Passing `NULL` into memstack functions will also manipulate the global memstack.*


## Contributors
Contributing helps keep this library safe and up to date. 
If you want to help, why not create an issue?

<a href="https://github.com/khhs167/memstack/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=khhs167/memstack" />
</a>
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

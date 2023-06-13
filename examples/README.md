## Examples
This directory contains many complete program examples to help understand how memstack works, and how to use memstack effectively.
Every example is commented and can be compiled using the command below.
```sh 
$ gcc <example-name>.c -lmemstack -o example && ./example && rm -rf example # Build, run and then delete the example
$ gcc <example-name>.c -lmemstack -o <example-name>.bin # Build the example, the .bin is a naming thing
```
You can also use the build script provided. 
The build script allows you to use `./build.sh` to build, run, and clean a given example.
```sh 
$ ./build.sh msnew 
```
On top of this, there's also the Makefile, written for GNUmake, but it should hopefully work on other Make versions.
```sh
make <example-name>.bin   # Build the example
make <example-name>.run   # Build and run the example
```
The reasoning for the `.bin` is simply for .gitignore easiness.

Each example has its own C file within the `memstack/example` folder.
There are also example that use the `global` memstack over a user created one.
Below is a table featuring the name of the example, its filename, and make command.
I recommend you read the C files as they all are commented to help you understand 
how to use memstack.

|       Name        |          Filename           |
|:-----------------:|:---------------------------:|
|       msnew       |       msnew_example.c       |
|      msfree       |      msfree_example.c       |
|      msalloc      |      msalloc_example.c      |
|      msclear      |      msclear_example.c      |
|       mspop       |       mspop_example.c       |
|      mspush       |      mspush_example.c       |
|    msrollback     |    msrollback_example.c     |
|   global_msnew    |   global_msnew_example.c    |
|   global_msfree   |   global_msfree_example.c   |
|  global_msalloc   |   gloal_msalloc_example.c   |
|  global_msclear   |  global_msclear_example.c   |
|   global_mspop    |   global_mspop_example.c    |
|   global_mspush   |   global_mspush_example.c   |
| global_msrollback | global_msrollback_example.c |

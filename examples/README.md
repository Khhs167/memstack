## Examples
This directory contains many complete program examples to help understand how memstack works, and how to use memstack effectively.
Every example is commented and can be compiled using the command below.
```sh 
$ gcc <example-name>.c -lmemstack -o example && ./example
```
You can also use the Makefile provided. 
The Makefile allows you to use `make` to build, run, and clean a given example.
```sh 
$ make 
```

Each example has its own C file within the `memstack/example` folder.
There are also example that use the `global` memstack over a user created one.
Below is a table featuring the name of the example, its filename, and make command.
I recommend you read the C files as they all are commented to help you understand 
how to use memstack.

|        Name         |          Filename           |
|:-------------------:|:---------------------------:|
|        msnew        |       msnew_example.c       |
|       msfree        |      msfree_example.c       |
|       msalloc       |      msalloc_example.c      |
|       msclear       |      msclear_example.c      |
|        mspop        |       mspop_example.c       |
|       mspush        |      mspush_example.c       |
|     msrollback      |    msrollback_example.c     |
|    global msnew     |   global_msnew_example.c    |
|    global msfree    |   global_msfree_example.c   |
|   global msalloc    |   gloal_msalloc_example.c   |
|   global msclear    |  global_msclear_example.c   |
|    global mspop     |   global_mspop_example.c    |
|    global mspush    |   global_mspush_example.c   |
|  global msrollback  | global_msrollback_example.c |

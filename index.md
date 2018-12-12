## Software Quality assurance for multiprocess systems in C/C++ language


### Abstarct

##### In low level languages like C, we face some common problems if we are accessing the memory (ram) frequently.

#### This repository is intended to be useful for developers who will begin to deal such a project , or already ongoing projects.   

# List of problems we discuss here:

1. Choosing convenient hardware and system components
  - Alternative tools and problem oriented design
  - Foreseeing the technology
  * Fast prototyping

  * Energy consumption

  * Portability


2. Dealing with possible future problems
  - Problems in C/C++
  - C based problems
  - Comparison of some possible solutions


```c
/* Declarations */


int (*cases[10])(int argc,...);
typedef int(*Case)(int argc,...);



typedef struct {
  int x;
  int y;
  int z;

}Datas;


  Datas *datas,*safedatas;


```


# Case1

Here we use the malloc function to get some memory from the system.
This function must be used carefully if really needed. In fact , we do use dynamic memory in other cases , and even pass some data to an other function.
In many years, i did not need to use malloc or its descendents.
Leaving the organization of those variables , even if they are dynamic, is just possible. see other cases...

```c
int case1(int argc, ...){
datas=(Datas*)malloc(sizeof(datas));

datas[0].x++; /* uninitialized values are dangerous.
compilers and valgrind does not give warnings.
*/

/*
we have just dropped a  memory leak here.
free( datas);
 */

/*  datas=NULL; /// This is the way to prevent some of the leakedges. */
return   datas[0].x;
}


```

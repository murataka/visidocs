#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <assert.h>

int (*cases[10])(int argc,...);
typedef int(*Case)(int argc,...);



typedef struct {
  int x;
  int y;
  int z;

}Datas;


  Datas *datas,*safedatas;

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


/*
  here, the compiler does not warn you.
  when the index "1" is a variable , things will
  get complicated.
*/
int case2(int argc ,...)
{
  datas[0].x=0;
/*  datas=NULL; */
return  datas[0].x;


}

/*
Anyway, we somehow may have to deal with dynamic memory.
So , what is the best way to prevent memory leakeges ?
*/

/* int case3(int datascount,Case afunction)*/
int case3(int argc,...){


      int val ;
     va_list ap;
     int i;
  Case f;
     va_start(ap, argc);

      val = va_arg(ap, int);
      if(argc>1){

        f=va_arg(ap, Case);

      }

      va_end(ap);


      Datas _datas[val] ;
/* compiler will give an error here. so...
     error: variable-sized object may not be initialized
       Datas _datas[val]={
    */


      datas=_datas;
      safedatas=_datas;
        _datas[val-1].x=rand()%20;
       datas[val-1].y=rand()%20;
       datas[val-1].z=rand()%20;
       datas[val].x++; /*
       valgrind does not warn when we reach an inaccessible address. ?
       */

  ((Case)f)(val,datas); /* here we pass dynamic data to case5.*/
  /*This data will be destroyed automatically when we exit this function.*/




    return _datas[0].x+_datas[0].y+_datas[val-1].z;


}
int case4(int n){
  Datas _datas[n] ;
return _datas[0].x;
}

/*
case 5 is called from case3. passing some dynamically created objects.
*/
int case5(int n,Datas* d){

assert(d!=NULL); /* assert will fail with detailed information..*/

  return 0;
}
int main(void){

int k;
cases[0]=&case1;
cases[1]=&case2;
cases[2]=&case3;


 srand(time(NULL));
 k=rand()%10;
 case4(3);
 case3(2,k+1,case5);

/*
case 2 accesses datas , which was not freed before.(case1 malloc)
*/
case2(1,3);

  return 0;
}

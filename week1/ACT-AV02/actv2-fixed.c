#include <sys/time.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>

int foo(){
  return(10);
}

long nanosec(struct timeval t){
  return((t.tv_sec*1000000+t.tv_usec)*1000);//converteix els segons en nanosegons
}

int main(){
  int i,j,res;
  long N_iterations=1000000;
  float avgT1, avgT2;
  struct timeval t1, t2;

  res=gettimeofday(&t1,NULL); assert(res==0);//agafa el temps del inici del primer bucle 
  for (i=0;i<N_iterations; i++){
    j=getpid();//cada iteracio crida a la funcio getpid
  }
  res=gettimeofday(&t2,NULL);   assert(res==0);//temps del final del bucle de getpid

  avgT1 =
  (nanosec(t2) - nanosec(t1))/(N_iterations*1.0);//mitjana del bucle, sabem quant triga de mitjana getpid, funcio que utilitza crides a sistema
  /* Find average time for Function call */
  res=gettimeofday(&t1,NULL);  assert(res==0); //agafa el temps del inici del segon bucle
  for (i=0;i<N_iterations; i++){
    j=foo();//cada iteració crida a funcio foo
  }
  res=gettimeofday(&t2,NULL);   assert(res==0);//temps del final del bucle funcio foo, fent crides a procediment

  avgT2 =
  (nanosec(t2) - nanosec(t1))/(N_iterations*1.0);//mitjana del bucle, sabem quant triga de mitjana la funcio foo
  printf("Time for 1 : %f\n",
  avgT1);
  printf("Time for 2 : %f\n",
  avgT2);

}

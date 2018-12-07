#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <string.h>
 
#define PI 3.14159265
#define STEP 0.0001
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

float modelo(float x, float sigma, float mu);
float *markov(int N,float sigma, float mu);
float randnorm (float m, float s);

FILE *out;

int main(int argc, char *argv[])
{


int N = atoi(argv[1]); //numero de puntos por cadena
float sig = atof(argv[2]);
float mu = atof(argv[3]);
float *t;
#pragma omp parallel
{
char names[64];

int t_id = omp_get_thread_num();
//char id[64];
sprintf(names,"samp_%d.txt",t_id);
//strcpy(names, "samp_");
//strcat(names,id);
//strcat(names, ".txt");
//names="samp_"+itoa(t_id)+".txt";
printf("Hola, soy el thread %d con nombre %s\n",t_id,names);
t= markov(N,sig,mu);
out=fopen(names,"w");



for(int j=0;j<N;j++){
//printf("%f \n",randnorm(mu,sig));
fprintf(out,"%f\n",t[j]);

}
fclose(out);
}   
//printf("%lf \n",modelo(0,1,0));
return 0;
}
 
 
float modelo(float x, float sigma, float mu){
float coef=1/(sqrt(2*PI*sigma*sigma));
return coef * exp((float)-pow(x-mu,2)/(2*sigma*sigma));
}


float *markov(int N,float sigma, float mu){

float *r = (float*) malloc(N * sizeof(float));
r[0]=mu;
//r[0]=((float)rand()/RAND_MAX);
//#pragma omp for
for(int i =1;i<N;i++){
srand48(i);
float act_val=modelo(r[i-1],sigma,mu);
float new_step=((float)randnorm(0,STEP))+r[i-1];
float new_val=modelo(new_step,sigma,mu);
if(new_val>act_val)
{
r[i]=new_step;
}


else
{
float R= MIN(1,(new_val/act_val));
//printf("%f\n",R);
float n_rand=((float)rand()/RAND_MAX);
if(n_rand<R)
{
r[i]=new_step;
}
else
{
r[i]=r[i-1];
}

}
}
return r;
}


float randnorm (float m, float s)
{
  float u1, u2, w, mult;
  static float X1, X2;
  static int call = 0;
 
  if (call == 1)
    {
      call = !call;
      return (m + s * (float) X2);
    }
 
  do
    {
      u1 = -1 + ((float) rand () / RAND_MAX) * 2;
      u2 = -1 + ((float) rand () / RAND_MAX) * 2;
      w = pow (u1, 2) + pow (u2, 2);
    }
  while (w >= 1 || w == 0);
 
  mult = sqrt ((-2 * log (w)) / w);
  X1 = u1 * mult;
  X2 = u2 * mult;
 
  call = !call;
 
  return (m + s * (float) X1);
}

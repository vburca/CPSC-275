/* Author: Vlad Burca, Ben Hartung
 * Date: 11/08/2011
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include<string.h>
/*
 * diffMat - This function returns the difference of A*B and C
 *
 *  Basic strategy:
 *    1. Compute a random vector x.
 *    2. Compute z = C*x.
 *    3. Compute y = B*x.
 *    4. Compute x = A*y.
 *    5. Compute the difference between x and z.
 */ 

double diffMat(double ** a, double ** b, double ** c,int N) // N: dimension of matrix
{
  double x[N], y[N], z[N],sum;
  int i, j;

  // generate a random vector
  for (i = 0; i < N; i++)
    x[i] = rand() % 100;

  // z = C x
  for (i = 0; i < N; i++) {
    sum = 0;
    for (j = 0; j < N; j++)
      sum += c[i][j] * x[j];
    z[i] = sum;
  }

  // y = B x
  for (i = 0; i < N; i++) {
    sum = 0;
    for (j = 0; j < N; j++)
      sum += b[i][j] * x[j];
    y[i] = sum;
  }

  // x = A y
  for (i = 0; i < N; i++) {
    sum = 0;
    for (j = 0; j < N; j++)
      sum += a[i][j] * y[j];
    x[i] = sum;
  }

  // compute the difference
  sum = 0;
  for (i = 0; i < N; i++) 
    sum += abs(x[i] - z[i]);

  return sum;
}

void mulVec(double ** matA, double * r,int n){
  int i,j;
  double sum;
  for(i=0;i<n;i++){
    sum = 0;
    for(j=0;j<n;j++){
      sum += r[i]*matA[i][j];
    }
    r[i] = sum;
  }
}

/*
double check(double ** matA, double** matB,double ** matC,double * r1,double * r2,int n){
  double sum = 0.0;
  int i;
  mulVec(matB,r1,n);
  mulVec(matA,r1,n);
  mulVec(matC,r2,n);

  for(i = 0;i<n;i++){
    printf("%f %f \n",r1[i],r2[i]);
    sum += abs(r1[i]-r2[i]);
  }
  printf("\n\n %f",sum);
  return sum;
}
*/

void mulMat(double ** matA, double** matB,double ** matC,int n){
  int i,j,k,sum;
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      sum = 0.0;
      for (k=0; k<n; k++)
		sum += matA[i][k] * matB[k][j];
      matC[i][j] = sum;
    }
  } 
}

void mulMat2(double ** matA, double** matB,double ** matC,int n,int a, int b,int c,int d,int e, int f){
  int i,j,k,sum;
  for (i=0; i<n; i++) {
    for (j=0; j<n; j++) {
      sum = 0.0;
      for (k=0; k<n; k++)
		sum += matA[i+a][k+b] * matB[k+c][j+d];
      matC[e+i][f+j] += sum;
    }
  } 
}

void blockMat(double ** matA, double** matB,double ** matC,int n){
  int newN = n/2;
  mulMat2(matA,matB,matC,newN,0*newN,0*newN,0*newN,0*newN,0*newN,0*newN);
  mulMat2(matA,matB,matC,newN,0*newN,1*newN,1*newN,0*newN,0*newN,0*newN);

  mulMat2(matA,matB,matC,newN,0*newN,0*newN,0*newN,1*newN,0*newN,1*newN);
  mulMat2(matA,matB,matC,newN,0*newN,1*newN,1*newN,1*newN,0*newN,1*newN);

  mulMat2(matA,matB,matC,newN,1*newN,0*newN,0*newN,0*newN,1*newN,0*newN);
  mulMat2(matA,matB,matC,newN,1*newN,1*newN,1*newN,0*newN,1*newN,0*newN);

  mulMat2(matA,matB,matC,newN,1*newN,0*newN,0*newN,1*newN,1*newN,1*newN);
  mulMat2(matA,matB,matC,newN,1*newN,1*newN,1*newN,1*newN,1*newN,1*newN);
}

void pBlockMat(double ** matA, double** matB,double ** matC,int n,int p){
  int newN = n/p;
  int cxInd,cyInd,m;

  for(cxInd = 0;cxInd<p;cxInd++)
    for(cyInd = 0;cyInd<p;cyInd++)
      for(m=0;m<p;m++)
		mulMat2(matA,matB,matC,newN,cxInd*newN,m*newN,m*newN,cyInd*newN,cxInd*newN,cyInd*newN);
}

void printMats(double ** matA, double** matB,double ** matC,int n){
  int i,j;
  for(i = 0; i<n;i++){
    for(j = 0; j<n;j++){
      printf("%.2f ",matA[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  for(i = 0; i<n;i++){
    for(j = 0; j<n;j++){
      printf("%.2f ",matB[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  for(i = 0; i<n;i++){
    for(j = 0; j<n;j++){
      printf("%.2f ",matC[i][j]);
    }
    printf("\n");
  }
}

int main(){
  int n = 9,p=3,method,doPrint;
  scanf("%d %d %d %d",&n,&p,&method,&doPrint);

  srand(time(NULL));
  double ** matA = (double **) malloc(n*sizeof(double));
  double ** matB = (double **) malloc(n*sizeof(double));
  double ** matC = (double **) malloc(n*sizeof(double));
  int i,j;

  for(i = 0; i<n;i++){
    matA[i] = (double *) malloc(n*sizeof(double));
    matB[i] = (double *) malloc(n*sizeof(double));
    matC[i] = (double *) malloc(n*sizeof(double));
  }

  for(i = 0; i<n;i++){
    for(j = 0; j<n;j++){
      matA[i][j] = rand() % 10;
      matB[i][j] = rand() % 10;
      matC[i][j] = 0;
    }
  }
  if(method)
    pBlockMat(matA,matB,matC,n,p);
  else
    mulMat(matA,matB,matC,n);
  if(doPrint)
    printMats(matA,matB,matC,n);

  printf("\n\n\n\n");
  printf("%f\n",diffMat(matA,matB,matC,n));
  // printf("%f",check(matA,matB,matC,r1,r2,n));
  for(i=0;i<n;i++){
    free(matA[i]);
    free(matB[i]);
    free(matC[i]);
  }
  free(matA);
  free(matB);
  free(matC);
  return 0;
}

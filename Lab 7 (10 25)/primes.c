#include <stdio.h>

#define N 100

int isprime(int n)
{
   int i;
   for (i = 2; i <= n/2; i++)
      if (!(n % i))
         return 0;
   return 1;
}
      
int main()
{
   int num;
   for (num = 3; num < N; num++)
      if (isprime(num))
         printf("%d\n", num);
}

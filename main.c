#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
#include "math.h"

struct data
{
    int sign;
    int e;
    int n;
};

int gcd (int a, int b) {
	if (b == 0)
		return a;
	else
		return gcd (b, a % b);
}

int H()
{
    return rand()%100;
}

struct data RSA(int p,int q,int h)
{
   int n;
   int sum = 1;
   int e,d,phi;
   int sign;
   struct data dat;
    
   n = p*q;
   phi = (p-1)*(q-1);


   while(gcd((p-1)*(q-1), e) != 1)
   {
        e = rand()%((p-1)*(q-1));
   }

   for(int i = 1; i < phi; i++)
   {
       if(i*e % phi == 1)
       {
           d = i;
       }
   }  

    for(int i = 0; i < d;i++)
    {
        sum = (sum*h)%n;
    }

    dat.e = e;
    dat.n = n;
    dat.sign = sum;

    return dat;
}

int main()
{
   int p,q,h;
   int sum = 1;
   struct data res;

   printf("Enter p: ");
   scanf("%d",&p);
   printf("Enter q: ");
   scanf("%d",&q);
    
   h = H();
   
   res = RSA(p,q,h); 

    for(int i = 0; i < res.e;i++)
    {
        sum = (sum*res.sign)%res.n;
    }

    if(h == sum)
    {
        printf("Right");
    }   
    else
    {
        printf("No");
    }
}
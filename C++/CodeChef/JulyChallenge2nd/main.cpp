#include <iostream>
#include <cmath>

#define MAX 100000

using namespace std;

int primes[MAX];

void gen_primes() 
     { 
       int i,j; 
       for(i=0;i<MAX;i++) primes[i] = 1; 
       for(i=2;i<=(int)sqrt(MAX);i++) 
         if (primes[i]) 
           for(j=i;j*i<MAX;j++) primes[i*j] = 0; 
     } 

int main(void)
{
	int i,j,pf=0,kp=0; //counters
	int t;
	cin>>t;
	gen_primes();
	while(t--)
	{
		kp=0;
		pf=0;
		int a,b,k;
		cin>>a>>b>>k;
		if(k==1){cout<<b-a+1<<endl; continue;}
		for(i=a;i<=b;++i)
		{
			if(primes[i]==1)continue;
			//count prime factors
			pf=0;
			for(j=2;j<=i/2;++j)
			{
				if(primes[j]==1&&i%j==0)++pf;
				if(pf==k){++kp; break;}
			}
		}
		cout<<kp<<endl;
	}
}

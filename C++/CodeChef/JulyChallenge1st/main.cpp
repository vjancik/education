#include <stdio.h>

int main(void) {
	int t;
	scanf("%d",&t);
	while(t--){
		int n,m,k;
		scanf("%d%d%d",&n,&m,&k);
		if((n==1&&m==1)||(n==1&&m==2)||(n==2&&m==1))printf("0\n");
		else if(n==1||m==1)printf("%d\n",k);
		else if(k>1) printf("%d\n",(k/2+k%2));
		else printf("1\n");
	}
	return 0;
}
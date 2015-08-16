#include <cstdio>

using namespace std;

int main(){
	unsigned int n,k,l;
	unsigned int r=1;//r is the position of the thumb
	scanf("%u %u %u",&n,&k,&l);
	unsigned long long output=0;
	if(l>=k){
		printf("0\n");
		return 0;
	}
	unsigned int x;
	for(int i=0;i!=n;++i){
		scanf("%u",&x);
		if(x>(r+l-1)){
			x-=r+l-1;
			output+=x;
			r+=x;
		}
		else if(x<r){
			x=r-x;
			output+=x;
			r-=x;
		}
	}
	printf("%llu\n",output);
	return 0;
}

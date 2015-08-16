#include <cstdio>

using namespace std;

int main(){
	int n;
	int x;
	int minx=0;
	long long int output=0;
	bool prev_contr=0;
	int size_prev_contr=0;
	scanf("%d",&n);
	while(n--){
		scanf("%d",&x);
		if(x>=minx){
			minx=x;
			prev_contr=0;
		}
		else if(x<minx&&prev_contr==0){
			output+=minx-x;
			prev_contr=1;
			size_prev_contr=minx-x;
		}
		else if(prev_contr==1&&minx-x>size_prev_contr){
			output+=minx-x-size_prev_contr;
			size_prev_contr=minx-x;
		}
		else if(prev_contr==1){
			size_prev_contr=minx-x;
		}
	}
	printf("%lld\n",output);
	return 0;
}

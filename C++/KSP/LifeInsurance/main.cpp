#include <cstdio>

using namespace std;

int main(){
	int n;
	int x;
	int minx=0;
	long long int output=0;
	bool predoslazmluva=0;
	int velkostpredoslejzmluvy=0;
	scanf("%d",&n);
	while(n--){
		scanf("%d",&x);
		if(x>=minx){
			minx=x;
			predoslazmluva=0;
		}
		else if(x<minx&&predoslazmluva==0){
			output+=minx-x;
			predoslazmluva=1;
			velkostpredoslejzmluvy=minx-x;
		}
		else if(predoslazmluva==1&&minx-x>velkostpredoslejzmluvy){
			output+=minx-x-velkostpredoslejzmluvy;
			velkostpredoslejzmluvy=minx-x;
		}
		else if(predoslazmluva==1){
			velkostpredoslejzmluvy=minx-x;
		}
	}
	printf("%lld\n",output);
	return 0;
}
#include <cstdio>

/*const int n=7;
int A[n] = {88,88,88,54,54,-2,-2};
int B[n];

int main(){
	int element,amount;
	int min=-2147483648;
	int i,j=0;
	while(j!=n){
		amount=0;
		element=2147483647;
		for(i=0;i<n;i++){
			if(A[i]<element&&A[i]>min){element=A[i];amount=1;}
			else if(A[i]==element){amount++;}
			}
		min=element;
		for(i=0;i<amount;i++){
			B[j]=element;
			j++;
		}
	}
	return 0;
}*/

// PRVA CAST - END

// DRUHA CAST

/*const int n=5;
int A[n] = {1,2,-367,1,8};
int B[n] = {1,1,2,-367,2};

int main(){
	int i,element,amount;
	int min=-2147483648;
	int max=-2147483648;
	for(i=0;i<n;i++){
		if(A[i]>max)max=A[i];
	}
	do {
		element=2147483647;
		amount=0;
		for(i=0;i<n;i++){
			if(A[i]<element&&A[i]>min){element=A[i];amount=1;}
			else if(A[i]==element){amount++;}
		}
		min=element;
		for(i=0;i<n;i++){
			if(B[i]==element)amount--;
		}
		if(amount!=0){
			printf("nie\n");
			return 0;
		}
	}while(element!=max);
	printf("ano\n");
	return 0;
}*/
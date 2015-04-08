#include<cstdio>

using namespace std;

int main(){
	int count=0;
	char character;
	int charactercounter=0;
	int r,s;
	scanf("%d %d",&r,&s);
	while(scanf("%c",&character)==1){
		++count;
		if(count==s)count=0;
		if(character=='|'){
			++charactercounter;
		}
		else
			charactercounter=0;
		if(charactercounter==3&&count>s/2){
			printf("doprava\n");
			return 0;
		}
		else if(charactercounter==3&&count<s/2) {
			printf("dolava\n");
			return 0;
		}
	}
}
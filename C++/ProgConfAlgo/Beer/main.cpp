#include <iostream>

using namespace std;

int machine1[20000],machine2[20000],spaces1[20000],spaces2[20000];
int dynamic[20000][2];

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;++i){
		cin>>machine1[i];
	}
	for(int i=0;i<n;++i){
		cin>>machine2[i];
	}
	for(int i=0;i<n-1;++i){
		cin>>spaces1[i];
	}
	for(int i=0;i<n-1;++i){
		cin>>spaces2[i];
	}
	dynamic[0][0]=machine1[0];
	dynamic[0][1]=machine2[0];
	int dynamic1=0,dynamic2=1;
	for(int i=1;i<n;++i){
		if(dynamic1==0){
			if(dynamic[i-1][0]+machine1[i]>dynamic[i-1][0]+spaces1[i-1]+machine2[i]){
				dynamic[i][0]=dynamic[i-1][0]+spaces1[i-1]+machine2[i];
				dynamic1=1;
			}
			else {
				dynamic[i][0]=dynamic[i-1][0]+machine1[i];
				dynamic1=0;
			}
		}
		else{
			if(dynamic[i-1][0]+machine2[i]>dynamic[i-1][0]+spaces2[i-1]+machine1[i]){
				dynamic[i][0]=dynamic[i-1][0]+spaces2[i-1]+machine1[i];
				dynamic1=0;
			}
			else {
				dynamic[i][0]=dynamic[i-1][0]+machine2[i];
				dynamic1=1;
			}
		}
		if(dynamic2==0){
			if(dynamic[i-1][1]+machine1[i]>dynamic[i-1][1]+spaces1[i-1]+machine2[i]){
				dynamic[i][1]=dynamic[i-1][1]+spaces1[i-1]+machine2[i];
				dynamic1=1;
			}
			else {
				dynamic[i][1]=dynamic[i-1][1]+machine1[i];
				dynamic1=0;
			}
		}
		else{
			if(dynamic[i-1][1]+machine2[i]>dynamic[i-1][1]+spaces2[i-1]+machine1[i]){
				dynamic[i][1]=dynamic[i-1][1]+spaces2[i-1]+machine1[i];
				dynamic1=0;
			}
			else {
				dynamic[i][1]=dynamic[i-1][1]+machine2[i];
				dynamic1=1;
			}
		}
	}
	cout<<min(dynamic[n-1][0],dynamic[n-1][1]);
	return 0;
}

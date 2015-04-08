#include <iostream>

using namespace std;

int stroj1[20000],stroj2[20000],medzeri1[20000],medzeri2[20000];
int dynamic[20000][2];

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;++i){
		cin>>stroj1[i];
	}
	for(int i=0;i<n;++i){
		cin>>stroj2[i];
	}
	for(int i=0;i<n-1;++i){
		cin>>medzeri1[i];
	}
	for(int i=0;i<n-1;++i){
		cin>>medzeri2[i];
	}
	dynamic[0][0]=stroj1[0];
	dynamic[0][1]=stroj2[0];
	int dynamic1=0,dynamic2=1;
	for(int i=1;i<n;++i){
		if(dynamic1==0){
			if(dynamic[i-1][0]+stroj1[i]>dynamic[i-1][0]+medzeri1[i-1]+stroj2[i]){
				dynamic[i][0]=dynamic[i-1][0]+medzeri1[i-1]+stroj2[i];
				dynamic1=1;
			}
			else {
				dynamic[i][0]=dynamic[i-1][0]+stroj1[i];
				dynamic1=0;
			}
		}
		else{
			if(dynamic[i-1][0]+stroj2[i]>dynamic[i-1][0]+medzeri2[i-1]+stroj1[i]){
				dynamic[i][0]=dynamic[i-1][0]+medzeri2[i-1]+stroj1[i];
				dynamic1=0;
			}
			else {
				dynamic[i][0]=dynamic[i-1][0]+stroj2[i];
				dynamic1=1;
			}
		}
		if(dynamic2==0){
			if(dynamic[i-1][1]+stroj1[i]>dynamic[i-1][1]+medzeri1[i-1]+stroj2[i]){
				dynamic[i][1]=dynamic[i-1][1]+medzeri1[i-1]+stroj2[i];
				dynamic1=1;
			}
			else {
				dynamic[i][1]=dynamic[i-1][1]+stroj1[i];
				dynamic1=0;
			}
		}
		else{
			if(dynamic[i-1][1]+stroj2[i]>dynamic[i-1][1]+medzeri2[i-1]+stroj1[i]){
				dynamic[i][1]=dynamic[i-1][1]+medzeri2[i-1]+stroj1[i];
				dynamic1=0;
			}
			else {
				dynamic[i][1]=dynamic[i-1][1]+stroj2[i];
				dynamic1=1;
			}
		}
	}
	cout<<min(dynamic[n-1][0],dynamic[n-1][1]);
	return 0;
}
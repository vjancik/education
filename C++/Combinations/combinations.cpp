#include <iostream>

using namespace std;

int main(){
	int N;
	int subset;
	int z;
	cout<<"Enter the number of elements. (use small number)"<<endl;
	cin>>N;
	int i=0;
	for(subset=0;subset<(1<<N);++subset){
		for(z=0;z<=N;++z){
			if(subset & 1<<z) cout<<z+1<<" ";
		}
		cout<<endl;
		++i;
	}
	cout<<"The number of combinations is "<<i-1<<endl;
	return 0;
}

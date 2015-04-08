#include <iostream>

using namespace std;

int zlavy[50000];

int main(){
	int n;//pocet zliav
	cin>>n;
	for(int i=0;i<n;++i){
		cin>>zlavy[i];
	}
	int start=0,end=0;
	int zlava=0,maxzlava=0;
	int maxstart=0,maxend=0;
	while(start!=n-1){
		if(zlavy[start]<0){
			zlava=zlavy[start];
			if(zlava<maxzlava){
				maxstart=start;
				maxend=end;
				maxzlava=zlava;
			}
			if(end!=n-1)
			while((zlava+=zlavy[++end])<0){
				if(zlava<maxzlava){
					maxzlava=zlava;
					maxstart=start;
					maxend=end;
				}
				if(end==n-1)break;
			}
			++start;
		} else {
			++start;
			end=start;
		}
	}
	cout<<maxstart+1<<" "<<maxend+1<<endl;
	return 0;
}
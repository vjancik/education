#include <iostream>

using namespace std;

int discounts[50000];

int main(){
	int n;//pocet zliav
	cin>>n;
	for(int i=0;i<n;++i){
		cin>>discounts[i];
	}
	int start=0,end=0;
	int discount=0,maxdiscount=0;
	int maxstart=0,maxend=0;
	while(start!=n-1){
		if(discounts[start]<0){
			discount=discounts[start];
			if(discount<maxdiscount){
				maxstart=start;
				maxend=end;
				maxdiscount=discount;
			}
			if(end!=n-1)
			while((discount+=discounts[++end])<0){
				if(discount<maxdiscount){
					maxdiscount=discount;
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

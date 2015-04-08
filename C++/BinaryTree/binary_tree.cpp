#include <iostream>
#include <iomanip>

using namespace std;

int hlbka=4;
int sirka=2;
int cisla[9]={1,2,3,4,5,6,7,8,9};

int main(){
	int i=1;
	int hlbkai=1;
	cout<<setw(2*hlbka)<<cisla[0]<<endl;
	while(i<=8){
		cout<<setw(hlbka/((hlbkai)));
		for(int help=0;help<2*hlbkai;++help){
			if(i<=8)cout<<cisla[i]<<setw(2*(hlbka/(hlbkai)));
			++i;
		}
		++hlbkai;
		cout<<endl;
	}
	return 0;
}

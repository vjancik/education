#include <iostream>

using namespace std;

int main() {
	bool i=true;
	short int x;
	while(i){	
		cin>>x;
		if(x==42)break;
		cout<<x<<endl;
	}
	return 0;
}
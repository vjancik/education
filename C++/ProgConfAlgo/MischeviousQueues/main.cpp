#include <iostream>
#include <string>

using namespace std;

int main(){
	int n;
	int borrow_before,borrow_after=1;
	string name;
	string Lux="Luxusko";
	cin>>n;
	for(int i=0;i<n;++i){
		cin>>name;
		if(name==Lux)borrow_before=i+1;
		else if(name.compare(Lux)<0)++borrow_after;
	}
	if(borrow_after>borrow_before){
		cout<<"o "<<borrow_after-borrow_before<<" dozadu"<<endl;
	}
	else if(borrow_after<borrow_before){
		cout<<"o "<<borrow_before-borrow_after<<" dopredu"<<endl;
	}
	else cout<<"neposunie sa"<<endl;
	return 0;
}

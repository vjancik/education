#include <iostream>
#include <string>

using namespace std;

int main(){
	int n;
	int poziciapred,poziciapo=1;
	string name;
	string Lux="Luxusko";
	cin>>n;
	for(int i=0;i<n;++i){
		cin>>name;
		if(name==Lux)poziciapred=i+1;
		else if(name.compare(Lux)<0)++poziciapo;
	}
	if(poziciapo>poziciapred){
		cout<<"o "<<poziciapo-poziciapred<<" dozadu"<<endl;
	}
	else if(poziciapo<poziciapred){
		cout<<"o "<<poziciapred-poziciapo<<" dopredu"<<endl;
	}
	else cout<<"neposunie sa"<<endl;
	return 0;
}
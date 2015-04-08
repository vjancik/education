#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
	short int c;
	cin>>c;
	while(c--){
		string s;
		string::iterator is;
		stack<char> pole;
		cin>>s;
		if (s.size()%2!=0){
			cout<<"NIE"<<endl;
			continue;
		}
		for(is=s.begin();is!=s.end();++is){
			if(*is=='{'||*is=='['||*is=='(') {
				pole.push(*is);
			}
			else if(!pole.empty()){
				if(*is=='}'&&pole.top()=='{') pole.pop();
				else if(*is==']'&&pole.top()=='[') pole.pop();
				else if(*is==')'&&pole.top()=='(') pole.pop();
				else {
					cout<<"NIE"<<endl;
					break;
				}
			}
			else{
				cout<<"NIE"<<endl;
				break;
			}
		}
		if(is==s.end()){
			if(pole.empty()){
				cout<<"ANO"<<endl;
			}
			else{
				cout<<"NIE"<<endl;
			}
		}
	}
	return 0;
}

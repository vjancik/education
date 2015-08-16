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
		stack<char> field;
		cin>>s;
		if (s.size()%2!=0){
			cout<<"NO"<<endl;
			continue;
		}
		for(is=s.begin();is!=s.end();++is){
			if(*is=='{'||*is=='['||*is=='(') {
				field.push(*is);
			}
			else if(!field.empty()){
				if(*is=='}'&&field.top()=='{') field.pop();
				else if(*is==']'&&field.top()=='[') field.pop();
				else if(*is==')'&&field.top()=='(') field.pop();
				else {
					cout<<"NO"<<endl;
					break;
				}
			}
			else{
				cout<<"NO"<<endl;
				break;
			}
		}
		if(is==s.end()){
			if(field.empty()){
				cout<<"YES"<<endl;
			}
			else{
				cout<<"NO"<<endl;
			}
		}
	}
	return 0;
}

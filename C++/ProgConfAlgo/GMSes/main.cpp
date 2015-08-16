#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > table;

int main(){
	string first,second;
	getline(cin,first);
	getline(cin,second);
	table.resize(second.size()+1);
	for(int i=0;i<second.size()+1;++i){
		table[i].resize(first.size()+1);
	}
	for(int y=0;y<second.size()+1;++y){
		table[y][0]=y;
	}
	for(int x=0;x<first.size()+1;++x)table[0][x]=x;
	for(int x=1;x<first.size()+1;++x){
		for(int y=1;y<second.size()+1;++y){
			if(first[x-1]==second[y-1]) table[y][x]=min(min(table[y][x-1]+1,table[y-1][x]+1),table[y-1][x-1]);
			else table[y][x]=min(min(table[y][x-1]+1,table[y-1][x]+1),table[y-1][x-1]+1);
		}
	}
	cout<<"Minimalny pocet operacii je "<<table[second.size()][first.size()]<<endl;
	return 0;
}

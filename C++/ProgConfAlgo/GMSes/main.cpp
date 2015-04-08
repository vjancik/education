#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > tabulka;

int main(){
	string prvy,druhy;
	getline(cin,prvy);
	getline(cin,druhy);
	tabulka.resize(druhy.size()+1);
	for(int i=0;i<druhy.size()+1;++i){
		tabulka[i].resize(prvy.size()+1);
	}
	for(int y=0;y<druhy.size()+1;++y){
		tabulka[y][0]=y;
	}
	for(int x=0;x<prvy.size()+1;++x)tabulka[0][x]=x;
	for(int x=1;x<prvy.size()+1;++x){
		for(int y=1;y<druhy.size()+1;++y){
			if(prvy[x-1]==druhy[y-1]) tabulka[y][x]=min(min(tabulka[y][x-1]+1,tabulka[y-1][x]+1),tabulka[y-1][x-1]);
			else tabulka[y][x]=min(min(tabulka[y][x-1]+1,tabulka[y-1][x]+1),tabulka[y-1][x-1]+1);
		}
	}
	cout<<"Minimalny pocet operacii je "<<tabulka[druhy.size()][prvy.size()]<<endl;
	return 0;
}
#include <iostream>
#include <fstream>

using namespace std;

char pole[2000][2000];
int r,s,n;

bool range_check(int hodnota,int limit){
	if(hodnota<0||hodnota>limit)return 0;
	return 1;
}

void nakresli_vlocku(int x,int y){
	/*for(int i=x-n,j=y-n;i<=x+n;++i,++j){
		if(range_check(i,s))pole[i][y]='#';
		else continue;
		if(range_check(j,r))pole[i][j]='#';
	}
	for(int j=y+n,i=x-n;j>=y-n;--j,++i){
		if(range_check(j,r))pole[x][j]='#';
		else continue;
		if(range_check(i,s))pole[i][j]='#';
	}*/
	for(int j=y-n;j<=y+n;++j){
		for(int i=x-n;i<=x+n;++i){
			if(range_check(i,s)&&range_check(j,r))pole[i][j]='#';
		}
	}

}

int main(){
	int i,j;
	cin>>r>>s>>n;
	for(j=0;j<r;++j){
		for(i=0;i<s;++i){
			pole[i][j]='.';
		}
	}
	for(j=0;j<r;++j){
		for(i=0;i<s;++i){
			char x;
			cin>>x;
			if(x=='#')nakresli_vlocku(i,j);
		}
	}
	nakresli_vlocku(8,0);
	for(j=0;j<r;++j){
		for(i=0;i<s;++i){
			cout<<pole[i][j];
		}
		cout<<endl;
	}
	return 0;
}
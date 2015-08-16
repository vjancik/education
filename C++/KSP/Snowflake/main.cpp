#include <iostream>
#include <fstream>

using namespace std;

char field[2000][2000];
int r,s,n;

bool range_check(int value,int limit){
	if(value<0||value>limit)return 0;
	return 1;
}

void paint_snowflake(int x,int y){
	/*for(int i=x-n,j=y-n;i<=x+n;++i,++j){
		if(range_check(i,s))field[i][y]='#';
		else continue;
		if(range_check(j,r))field[i][j]='#';
	}
	for(int j=y+n,i=x-n;j>=y-n;--j,++i){
		if(range_check(j,r))field[x][j]='#';
		else continue;
		if(range_check(i,s))field[i][j]='#';
	}*/
	for(int j=y-n;j<=y+n;++j){
		for(int i=x-n;i<=x+n;++i){
			if(range_check(i,s)&&range_check(j,r))field[i][j]='#';
		}
	}

}

int main(){
	int i,j;
	cin>>r>>s>>n;
	for(j=0;j<r;++j){
		for(i=0;i<s;++i){
			field[i][j]='.';
		}
	}
	for(j=0;j<r;++j){
		for(i=0;i<s;++i){
			char x;
			cin>>x;
			if(x=='#')paint_snowflake(i,j);
		}
	}
	paint_snowflake(8,0);
	for(j=0;j<r;++j){
		for(i=0;i<s;++i){
			cout<<field[i][j];
		}
		cout<<endl;
	}
	return 0;
}

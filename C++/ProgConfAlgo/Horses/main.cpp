#include <iostream>
#include <queue>
#define WIDTH 30
#define HEIGHT 20

using namespace std;


int pole[WIDTH][WIDTH];
queue<pair<int,int>> rada; //na spracovanie

bool range_check(int x, int y){
	if(x<0||x>WIDTH-1||y<0||y>HEIGHT-1) return 0;
	return 1;
}
void najdi_policka(){
	int x,y;
	while(!rada.empty()){
		x=rada.front().first;
		y=rada.front().second;
		rada.pop();
		if(range_check(x+2,y+1)&&pole[x+2][y+1]==-1) {rada.push(pair<int,int>(x+2,y+1)); pole[x+2][y+1]=pole[x][y]+1;}
		if(range_check(x+2,y-1)&&pole[x+2][y-1]==-1) {rada.push(pair<int,int>(x+2,y-1)); pole[x+2][y-1]=pole[x][y]+1;}
		if(range_check(x+1,y+2)&&pole[x+1][y+2]==-1) {rada.push(pair<int,int>(x+1,y+2)); pole[x+1][y+2]=pole[x][y]+1;}
		if(range_check(x+1,y-2)&&pole[x+1][y-2]==-1) {rada.push(pair<int,int>(x+1,y-2)); pole[x+1][y-2]=pole[x][y]+1;}
		if(range_check(x-1,y+2)&&pole[x-1][y+2]==-1) {rada.push(pair<int,int>(x-1,y+2)); pole[x-1][y+2]=pole[x][y]+1;}
		if(range_check(x-1,y-2)&&pole[x-1][y-2]==-1) {rada.push(pair<int,int>(x-1,y-2)); pole[x-1][y-2]=pole[x][y]+1;}
		if(range_check(x-2,y+1)&&pole[x-2][y+1]==-1) {rada.push(pair<int,int>(x-2,y+1)); pole[x-2][y+1]=pole[x][y]+1;}
		if(range_check(x-2,y-1)&&pole[x-2][y-1]==-1) {rada.push(pair<int,int>(x-2,y-1)); pole[x-2][y-1]=pole[x][y]+1;}
	}
}

int main(){
	for(int j=0;j<HEIGHT;++j){
		for(int i=0;i<WIDTH;++i){
			pole[i][j]=-1;
		}
	}
	pole[14][9]=0;
	rada.push(pair<int,int>(14,9));
	najdi_policka();
	for(int j=0;j<HEIGHT;++j){
		for(int i=0;i<WIDTH;++i){
			cout<<pole[i][j];
		}
		cout<<endl;
	}
	cin.get();
	return 0;
}
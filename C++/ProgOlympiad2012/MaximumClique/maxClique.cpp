#include <cstdio>
#include <map>
#include <vector>

using namespace std;

map<int,int> field[100001];
int n,m; //number of spies, number of pairs
int candidates[7]; //candidates
int output[7]; //output
int l;
int maxl=0; //size of the largest clique

int checkconnections(int x){
	for(int i=0;i<=l;++i){
		if(field[candidates[i]].find(x)==field[candidates[i]].end()) return 0;
	}
	return 1;
}

int findelement(int y){
	for(map<int,int>::iterator it=field[y].begin();it!=field[y].end();++it){
		if(it->second==1)continue;
		if(checkconnections(it->first)) {
			candidates[++l]=it->first;
			it->second=1;
			return 1;
		}
	}
	return 0;
}

int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	if(m==0){printf("%d\n",n); return 0;}
	for(int i=1;i<=m;++i){
		scanf("%d%d",&x,&y);
		if(x<y)field[x].insert(pair<int,int>(y,0));
		else field[y].insert(pair<int,int>(x,0));
	}
	if(m==1) {printf("%d %d\n",x,y); return 0;}
	for(int i=1;i<=n;++i){
		candidates[0]=i;
		for(map<int,int>::iterator it=field[i].begin();it!=field[i].end();++it){
			if(it->second==1)continue;
			candidates[1]=it->first;
			it->second=1;
			l=1;
			while(findelement(candidates[l])){
				if(l==6){
					for(int i=0;i<=l;++i){
						printf(" %d",candidates[i]);
					}
					printf("\n");
					return 0;
				}
			}
			if(l>maxl){
				for(int j=0;j<=l;++j){
					output[j]=candidates[j];
				}
				maxl=l;
			}
		}
	}
	for(int i=0;i<=maxl;++i){
		printf(" %d",output[i]);
	}
	printf("\n");
	return 0;
}

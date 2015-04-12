#include <cstdio>
#include <map>
#include <vector>

using namespace std;

map<int,int> pole[100001];
int n,m; //pocet spionov, pocet dvojic
int kandidati[7]; //kandidati
int vystup[7]; //vystup
int l; //pocet kandidatov (pomocna premenna)
int maxl=0; //velkost najvecsej kliky

int checkconnections(int x){
	for(int i=0;i<=l;++i){
		if(pole[kandidati[i]].find(x)==pole[kandidati[i]].end()) return 0;
	}
	return 1;
}

int findelement(int y){
	for(map<int,int>::iterator it=pole[y].begin();it!=pole[y].end();++it){
		if(it->second==1)continue;
		if(checkconnections(it->first)) {
			kandidati[++l]=it->first;
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
		if(x<y)pole[x].insert(pair<int,int>(y,0));
		else pole[y].insert(pair<int,int>(x,0));
	}
	if(m==1) {printf("%d %d\n",x,y); return 0;}
	for(int i=1;i<=n;++i){
		kandidati[0]=i;
		for(map<int,int>::iterator it=pole[i].begin();it!=pole[i].end();++it){
			if(it->second==1)continue;
			kandidati[1]=it->first;
			it->second=1;
			l=1;
			while(findelement(kandidati[l])){
				if(l==6){
					for(int i=0;i<=l;++i){
						printf(" %d",kandidati[i]);
					}
					printf("\n");
					return 0;
				}
			}
			if(l>maxl){
				for(int j=0;j<=l;++j){
					vystup[j]=kandidati[j];
				}
				maxl=l;
			}
		}
	}
	for(int i=0;i<=maxl;++i){
		printf(" %d",vystup[i]);
	}
	printf("\n");
	return 0;
}
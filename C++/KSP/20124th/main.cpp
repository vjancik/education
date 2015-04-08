#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

vector<vector<int> > pole;
unsigned int t;
void init(){
	unsigned int n=0;
	unsigned int x,k,p;
	scanf("%u %u %u", &k,&p,&t);
	pole.resize(p);
	while(n<k) {
		scanf("%u", &x);
		pole[0].push_back(x);
		n++;
	}
}
int main(){
	init();
	unsigned int ki,pi,ti,piti;
	vector<int>::iterator it2;
	for(unsigned int i=0;i!=t;++i){		
		scanf("%u %u %u", &ki,&pi,&ti);
		if(ti==0)continue;
		--pi;
		piti=pi+ti;
		it2=find(pole[pi].begin(),pole[pi].end(),ki);
		pole[piti].insert(pole[piti].end(), it2, pole[pi].end());
		it2=find(pole[pi].begin(),pole[pi].end(),ki);
		pole[pi].erase(it2,pole[pi].end());
	}
	for(vector<vector<int> >::iterator it=pole.begin();it!=pole.end();++it){
		if(it->empty()){
			printf("0\n");
		}
		else{
			printf("%u ",it->size());
			for(vector<int>::iterator it2=it->begin();it2!=it->end();++it2){
				if(*it2==it->back())printf("%d\n",*it2);
				else printf("%d ",*it2);
			}
		}
	}
return 0;
}	
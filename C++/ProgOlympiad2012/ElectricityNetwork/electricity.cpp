#include <cstdio>
#include <vector>

using namespace std;

class entita
{
	public:
		char z;
		unsigned int m,c,d;
		entita ();
		entita (char zi,unsigned int mi,unsigned int ci,unsigned int di) {z=zi;c=ci;d=di;m=mi;};
};

vector <entita> siet;
vector <int> vystup;


int main(){
	int n,d1,mi,ci,di;
	char zi;
	scanf("%d %d",&n,&d1);
	scanf(" %c %d %d %d",&zi,&mi,&ci,&di);
	if(ci<d1||di<d1){
		printf("nemozne\n");
		return 0;
	}
	entita a(zi,mi,ci,di);
	siet.resize(n+1,a);
	vystup.resize(n+1,0);
	vystup[1]=2;
	vystup[2]=2;
	for(int i=3;i<=n;i++){
		scanf(" %c %d %d %d",&zi,&mi,&ci,&di);
		if(zi=='M'&&ci<di) {
			printf("nemozne\n");
			return 0;
		}
		else if(zi=='E') vystup[i]=i;
		entita a(zi,mi,ci,di);
		siet[i]=a;
	}
	vector<entita>::reverse_iterator it;
	for(it=siet.rbegin();it!=siet.rend()-2;it++){
		if(it->z=='M'){
			if(it->d>it->c){
				printf("nemozne\n");
				return 0;
			}
			if(siet[it->m].z=='M')siet[it->m].d+=it->d;
			else siet[it->m].d-=it->d;
		}
		else {
			if(it->d<0){
				printf("nemozne\n");
				return 0;
			}
		}
	}
	vector<int>::iterator it2=vystup.begin()+2;
	int ele = *it2;
	for(it2;it2!=vystup.end();it2++){
		if(*it2==0) *it2=ele;
		else ele=*it2;
	}
	for(it2=vystup.begin()+1;it2!=vystup.end()-1;it2++){
		printf("%d ",*it2);
	}
	printf("%d\n",vystup.back());
	return 0;
}
#include <cstdio>
#include <vector>

using namespace std;

class entity
{
	public:
		char z;
		unsigned int m,c,d;
		entity ();
		entity (char zi,unsigned int mi,unsigned int ci,unsigned int di) {z=zi;c=ci;d=di;m=mi;};
};

vector <entity> network;
vector <int> output;


int main(){
	int n,d1,mi,ci,di;
	char zi;
	scanf("%d %d",&n,&d1);
	scanf(" %c %d %d %d",&zi,&mi,&ci,&di);
	if(ci<d1||di<d1){
		printf("nemozne\n");
		return 0;
	}
	entity a(zi,mi,ci,di);
	network.resize(n+1,a);
	output.resize(n+1,0);
	output[1]=2;
	output[2]=2;
	for(int i=3;i<=n;i++){
		scanf(" %c %d %d %d",&zi,&mi,&ci,&di);
		if(zi=='M'&&ci<di) {
			printf("nemozne\n");
			return 0;
		}
		else if(zi=='E') output[i]=i;
		entity a(zi,mi,ci,di);
		network[i]=a;
	}
	vector<entity>::reverse_iterator it;
	for(it=network.rbegin();it!=network.rend()-2;it++){
		if(it->z=='M'){
			if(it->d>it->c){
				printf("nemozne\n");
				return 0;
			}
			if(network[it->m].z=='M')network[it->m].d+=it->d;
			else network[it->m].d-=it->d;
		}
		else {
			if(it->d<0){
				printf("nemozne\n");
				return 0;
			}
		}
	}
	vector<int>::iterator it2=output.begin()+2;
	int ele = *it2;
	for(it2;it2!=output.end();it2++){
		if(*it2==0) *it2=ele;
		else ele=*it2;
	}
	for(it2=output.begin()+1;it2!=output.end()-1;it2++){
		printf("%d ",*it2);
	}
	printf("%d\n",output.back());
	return 0;
}

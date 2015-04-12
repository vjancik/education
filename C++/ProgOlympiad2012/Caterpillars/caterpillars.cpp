#include <cstdio>
#include <cmath>
#include <map>

#define PI 3.14159265

using namespace std;

class bod{
public:
	bool druhy;
	int x,y;
	bod(int xx, int yy) {x=xx; y=yy; druhy=1;}
};
multimap<float,bod> kruznica;
unsigned int I=0,maxI;
bod maxIpos(0,0);

int main(){
	unsigned int n;
	scanf("%u",&n);
	float x1,y1,x2,y2;
	float result1,result2;
	while(n--){
		scanf("%f %f %f %f",&x1,&y1,&x2,&y2);
		result1=atan2(y1,x1)*180/PI;
		result2=atan2(y2,x2)*180/PI;
		if(result1<0)result1+=360;
		if(result2<0)result2+=360;
		bod Bod(x1,y1);
		bod Bod2(x2,y2);
		if(result1>(result2+180)||result2>(result1+180)){
			if(result1>result2){
				Bod.druhy=0;
				kruznica.insert(pair<float,bod>(result1,Bod));
				kruznica.insert(pair<float,bod>(result2,Bod2));
				++I;
			}
			else{
				Bod2.druhy=0;
				kruznica.insert(pair<float,bod>(result2,Bod2));
				kruznica.insert(pair<float,bod>(result1,Bod));
				++I;
			}
		}
		else{
			if(result1>result2){
				Bod2.druhy=0;
				kruznica.insert(pair<float,bod>(result2,Bod2));
				kruznica.insert(pair<float,bod>(result1,Bod));
			}
			else{
				Bod.druhy=0;
				kruznica.insert(pair<float,bod>(result1,Bod));
				kruznica.insert(pair<float,bod>(result2,Bod2));
			}
		}
	}
	maxI=I;
	multimap<float,bod>::iterator it;
	for(it=kruznica.begin();it!=kruznica.end();++it){
		if(it->second.druhy==0){
			++I;
		}
		else {
			--I;
		}
		if(I>maxI){
			maxIpos.x=it->second.x;
			maxIpos.y=it->second.y;
			maxI=I;
		}
	}
	printf("%d %d\n",maxIpos.x,maxIpos.y);
	return 0;
}
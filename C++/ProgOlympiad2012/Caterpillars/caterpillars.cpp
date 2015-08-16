#include <cstdio>
#include <cmath>
#include <map>

#define PI 3.14159265

using namespace std;

class point{
public:
	bool second;
	int x,y;
	point(int xx, int yy) {x=xx; y=yy; second=1;}
};
multimap<float,point> circle;
unsigned int I=0,maxI;
point maxIpos(0,0);

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
		point point(x1,y1);
		point point2(x2,y2);
		if(result1>(result2+180)||result2>(result1+180)){
			if(result1>result2){
				point.second=0;
				circle.insert(pair<float,point>(result1,point));
				circle.insert(pair<float,point>(result2,point2));
				++I;
			}
			else{
				point2.second=0;
				circle.insert(pair<float,point>(result2,point2));
				circle.insert(pair<float,point>(result1,point));
				++I;
			}
		}
		else{
			if(result1>result2){
				point2.second=0;
				circle.insert(pair<float,point>(result2,point2));
				circle.insert(pair<float,point>(result1,point));
			}
			else{
				point.second=0;
				circle.insert(pair<float,point>(result1,point));
				circle.insert(pair<float,point>(result2,point2));
			}
		}
	}
	maxI=I;
	multimap<float,point>::iterator it;
	for(it=circle.begin();it!=circle.end();++it){
		if(it->second.second==0){
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

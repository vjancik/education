#include <cstdio>
#include <set>

using namespace std;

multiset<int> first,second;
int main() {
	unsigned int n,m,x;
	scanf("%u %u",&n,&m);
	for(int i=0;i!=n;++i){
		scanf("%u",&x);
		first.insert(x);
	}
	for(int i=0;i!=m;++i){
		int x;
		scanf("%u",&x);
		second.insert(x);
	}
	for(multiset<int>::iterator it=first.begin();it!=first.end();++it){
		multiset<int>::iterator it2 = second.find(*it);
		if(it2==second.end()){
			printf("%u\n",*it);
			return 0;
		}
	}
	return 0;
}
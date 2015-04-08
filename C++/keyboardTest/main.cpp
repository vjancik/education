#include <conio.h>
#include <iostream>
using namespace std;
int x=1;
int main() {
	//for(x=1;x<102;x++) {
	while(1) {
		if(kbhit())
        {
            int c = getch();
			if(c==119) cout<<"UP"<<endl;
			if(c==115) cout<<"DOWN"<<endl;
			if(c==97) cout<<"LEFT"<<endl;
			if(c==100) cout<<"RIGHT"<<endl;
			if(c==32) cout<<"FIRE!"<<endl;
        }
	}
}
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int startingMoney = 1000000000;
long long money = 1000000000;
int blinkPrice = 2500000;
int blinks = 1;
int reward = 13500000;	
int testCases = 1000;

int main() {
	int allWins=0;
	int allBlinks=0;
	int fullRound=0;
	int mostRounds=0;
	int casesCounter=0;
	long long averageHighestMoney=0;
	int mostHighestMoney=0;
	srand(time(NULL));
	while(casesCounter<testCases){
		int counterWon = 0, counterLost = 0;
		int number;
		int highestMoney=0;
		money = startingMoney;
		while(money>=blinkPrice*blinks)
		{
			number = rand() % 8 + 1;
			money -= blinkPrice*blinks;
			if(number==6)
			{
				++counterWon;
				money+= reward;
				if(money>highestMoney)highestMoney=money;
				//cout<<"Bet number: "<<counterWon+counterLost<<" -> You won, current money: "<<money<<" ISK."<<endl;
			} else {
				++counterLost;
			}
		}
		if(highestMoney<startingMoney)highestMoney=startingMoney;
		averageHighestMoney+=highestMoney;
		if(mostHighestMoney<highestMoney)mostHighestMoney=highestMoney;
		if(counterWon+counterLost>=100) ++fullRound;
		if(counterWon+counterLost>mostRounds) mostRounds=counterWon+counterLost;
		allBlinks+=counterLost+counterWon;
		allWins+=counterWon;
		++casesCounter;
	}
	averageHighestMoney/=testCases;
	cout<<"FINISHED"<<endl;
	cout<<allWins<<" wins out of "<<allBlinks<<" blinks."<<endl;
	cout<<fullRound<<" successful rounds out of "<<testCases<<endl;
	cout<<"Most rounds in 1 test case achieved: "<<mostRounds<<endl;
	cout<<"Most money ever held: "<<mostHighestMoney<<endl;
	cout<<"Average highest money: "<<averageHighestMoney;
	cin.get();
	return 0;
}
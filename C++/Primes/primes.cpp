#include <iostream>
#include <cstdio>
#include <ctime>
#include <fstream>

using namespace std;

double diffclock(clock_t clock1, clock_t clock2) {

	double diffticks = clock1 - clock2;
	double diffms = diffticks / (CLOCKS_PER_SEC / 1000);

	return diffms;
}

int main() {
	int limit, number, factor;
	bool prime = true;

	clock_t start, pstart, pend;
	double duration;

	ofstream primes;

	cin >> limit;
	
	primes.open("primes.txt");

	start = clock();
	pstart = clock();
	for (number = 4; number < limit; ++number)
	{
		for (factor = 2; factor <= (number / 2); ++factor)
		{
			if (number % factor == 0)
			{
				prime = false;
				break;
			}
		}
		if (prime == true) 
		{
			pend = clock();
			duration = diffclock(pend, pstart);
			primes << "Number " << number << " is a prime. " << "Time: "<< duration << " miliseconds." << endl;
			pstart = clock();
		}
		else
			prime = true;
	}
	primes << "Total time: " << diffclock(pstart, start) << " milliseconds." << endl;
	primes.close();
	return 0;
}
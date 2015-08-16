#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <clocale>

using namespace std;

string lowercaseacc    = "áäčďéíĺľňóôöŕšťúýž";
string uppercaseacc    = "ÁÄČĎÉÍĹĽŇÓÔÖŔŠŤÚÝŽ";
string lowercasedeacc  = "aacdeillnooorstuyz";
string uppercasedeacc  = "AACDEILLNOOORSTUYZ";

string sUppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string sLowercase = "abcdefghijklmnopqrstuvwxyz";

void simplify(int x){
	if (x == 138) x = 83;
	else if (x == 142) x = 90;
	else if (x == 154) x = 115;
	else if (x == 158) x = 122;
	else if (x >= 192 && x <= 197) x = 65;
	else if (x >= 200 && x <= 203) x = 69;
	else if (x >= 204 && x <= 207) x = 73;
}

string fLowercase(string x)
{
	int i, upper;
	for (i = 0; i < x.size(); ++i)
	{
		upper = sUppercase.find(x[i]);
		if (upper != -1)
			x[i] = sLowercase[upper];
	}
	return x;
}

string deaccent(string x, bool casesensitive){
	int i;
	int special;
	if (casesensitive == true)
	{
		for (i = 0; i < x.size(); ++i)
		{
			special = lowercaseacc.find(x[i]);
			if (special == -1) {
				special = uppercaseacc.find(x[i]);
				if (special == -1)
					continue;
				x[i] = uppercasedeacc[special];
				continue;
			}
			x[i] = lowercasedeacc[special];

		}
	}
	else {
		for (i = 0; i < x.size(); ++i)
		{
			special = lowercaseacc.find(x[i]);
			if (special == -1) {
				special = uppercaseacc.find(x[i]);
				if (special == -1)
					continue;
				x[i] = lowercasedeacc[special];
				continue;
			}
			x[i] = lowercasedeacc[special];

		}
		x = fLowercase(x);
	}
	return x;
}


int main() {
	setlocale(LC_CTYPE, "sk_SK");
	
	int i, slash;
	unsigned char letter;
	ifstream input("sk_sk.txt");
	ofstream output;
	
	string line;
	
	output.open("accentedDictionary.txt"); //ZMENIT VYSTUPNY SUBOR
	if (input.is_open())
	{
		while (getline(input, line))
		{
			slash = line.find('/');
			if (slash != -1)
				line = line.substr(0, slash);
			//line = deaccent(line, false);

			output << line << endl;
		}
		input.close();
		output.close();
	}
	
	else cout << "Unable to open file";

	return 0;
}


#include<string>
#include "error.h"
using namespace std;

void error(string s)
{
	cout << s << endl;
	system("pause");
	exit(1);
}

void expect(string s)
{
	cout << s << endl;

	system("pause");

	exit(1);
}
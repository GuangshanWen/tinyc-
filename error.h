#include<iostream>
#include<string>
using namespace std;

#ifndef __ERROT__
#define __ERROR__

void error(string s)
{
	cout << s << endl;
	system("pause");
	exit(1);
}


#endif

#include "lexer.h"
using namespace std;

string source_code;


vector<Tokener> t_vec;

int main()
{
	ifstream f("hello.txt");


	init(f,source_code);

	
	
	system("pause");
	return 1;
}
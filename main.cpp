
#include "lexer.h"
#include "parser.h"


vector<Tokener> t_vec;
string source_code;

int main()
{
	ifstream f("hello.txt");


	init(f,source_code);

	string_to_token(source_code,t_vec);
	
	 print();//¥Ú”°token

	cout << endl;
	system("pause");
	return 1;
}
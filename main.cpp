
#include "lexer.h"
#include "parser.h"
using namespace std;

string source_code;


vector<Tokener> t_vec;

int main()
{
	ifstream f("hello.txt");

	int ;

	init(f,source_code);

	string_to_token(source_code,t_vec);
	
	 print();

	cout << endl;
	system("pause");
	return 1;
}
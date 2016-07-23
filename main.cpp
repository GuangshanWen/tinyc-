
#include "lexer.h"
using namespace std;

string source_code;


vector<Tokener> t_vec;

int main()
{
	ifstream f("hello.txt");


	init(f,source_code);

	string_to_token(source_code,t_vec);
	
	cout << "lexer works !"<< endl;

	for (int i = 0;i<t_vec.size();++i)
	{
		cout << t_vec[i].s << " ";
	}
	cout << endl;
	system("pause");
	return 1;
}
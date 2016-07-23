#include "parser.h"
#include <vector>
#include "lexer.h"
#include "TOKEN.h"
using namespace std;

extern vector<Tokener> t_vec;
int index = 0;

void print()
{
	for (size_t i = 0;i<t_vec.size();++i)
	{
		cout << t_vec[i].s << " ";
	}
	cout << endl;
	for (size_t i = 0;i<t_vec.size();++i)
	{
		cout << t_vec[i].t << " ";
	}
}
Token get_token()
{
	return TK_EOF;
}

void parser(vector<Token> vec)
{
	while(get_token() != TK_EOF)
	{

	}
}


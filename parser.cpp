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

void init()
{
	
}

Token get_token()
{
	return t_vec[index++].t;
}

void roll_back()
{
	index --;
}

bool is_type(Token t)
{
	return ( t == TK_INT || t == TK_STRUCT || t == TK_VOID || t == TK_SHORT /
		     t == TK_CHAR );
}

void parse_declar()
{

}

void parser(vector<Token> vec)
{
	Token tmp;
	while(true)
	{
		tmp = get_token();
		if (tmp == TK_EOF)break;

		if(is_type(tmp))
		{
			parse_declar();
		}
	}
}


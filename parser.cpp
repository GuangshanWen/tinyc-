#include "parser.h"
#include <vector>
#include "lexer.h"
#include<assert.h>
#include "TOKEN.h"
using namespace std;
//
extern vector<Tokener> t_vec;
int index = 0;
Token token;

void print_token()
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

void skip(Token t)
{
	assert(token == t);
	get_token();
}

void is_type(Token t = token)
{
	assert(t == TK_INT || TK_CHAR || TK_SHORT);
}

void sizeof_expression()
{
	get_token();
	skip(TK_OPENPA);
	is_type();
	skip(TK_CLOSEPA);
}

void primary_expression()
{
	int t;
	switch(token)
	{
	case TK_CINT:
	case TK_CCHAR:
		get_token();
		break;

	case TK_CSTR:
		get_token();
		break;

	case TK_OPENPA:
		get_token();
		expression();
		skip(TK_CLOSEPA);
		break;

	default :
		t = token;
		get_token();

		if(t != TK_INDENT)
			expect("need indent!");
		break;
	}
}

void argument_list_expression()
{
	get_token();

	if(token != TK_CLOSEPA)
	{
		for(;;)
		{
			assignment_expression();

			if(token == TK_CLOSEPA)
				break;
			skip(TK_COMMA);
		}
	}

	skip(TK_CLOSEPA);
}

void postfix_expression()
{
	primary_expression();
	while(1)
	{
		if(token == TK_OPENBR)
		{
			get_token();
			expression();
			skip(TK_CLOSEBR);
		}

		else if(token == TK_OPENPA)
		{
			argument_list_expression();
		}
		else break;
	}
}

void get_token()
{
	token = t_vec[index].t;
	index++;
}

void unary_expression()
{
	switch(token)
	{
	case TK_AND:
		get_token();
		unary_expression();
		break;

	case TK_STAR:
		get_token();
		unary_expression();
		break;

	case TK_PLUS:
		get_token();
		unary_expression();
		break;

	case TK_MINUS :
		get_token();
		unary_expression();
		break;

	case TK_SIZEOF:
		get_token();
		sizeof_expression();
		break;

	default:
		postfix_expression();
		break;
	}
}

void multiplicative_expression()
{
	unary_expression();
	while(token == TK_STAR || token == TK_DIVIDE || token == TK_MOD)
	{
		get_token();
		unary_expression();
	}
}

void addictive_expression()
{
	multiplicative_expression();
	while(token == TK_PLUS || token == TK_MINUS)
	{
		get_token();
		multiplicative_expression();
	}
}

void relationnal_expression()
{
	addictive_expression();

	while(token == TK_LT || token == TK_LEQ || token == TK_GT || token == TK_GEQ)
	{
		get_token();
		addictive_expression();
	}
}

void equality_expression()
{
	relationnal_expression();

	while(token == TK_EQ || token == TK_NEQ)
	{
		get_token();
		relationnal_expression();
	}
}

void assignment_expression()
{
	equality_expression();

	if(token == TK_ASSIGN)
	{
		get_token();
		assignment_expression();
	}
}

void expression()
{
	get_token();
	while(true)
	{
		assignment_expression();

		if(token != TK_COMMA)
			break;

		get_token();
	}
}
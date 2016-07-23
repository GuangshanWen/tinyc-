#include "parser.h"
#include <vector>
#include "lexer.h"
#include "TOKEN.h"
using namespace std;
//
extern vector<Tokener> t_vec;
int index = 0;
//
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

//void init()
//{
//	
//}
//
//Token get_token()
//{
//	token = t_vec[index++].t;
//	return token;
//}
//
//void roll_back()
//{
//	index --;
//}
//
//bool is_type(Token t)
//{
//	return ( t == TK_INT || t == TK_STRUCT || t == TK_VOID || t == TK_SHORT /
//		     t == TK_CHAR );
//}
//
//bool is_call(Token t) //判断是不是调用约定
//{
//	return t == KW_CDECL || t == KW_STDCALL;
//}
//
//void parse_function()
//{
//
//}
//
//void parse_declar()
//{
//	while(get_token() == TK_STAR); // 如果是*，表示这里有指针
//
//	if(is_call(get_token()))
//	{
//		parse_function();
//	}
//	roll_back(); // 回退
//
//	if(get_token() != TK_INDENT)
//		error("systax error : there should be an indent!");
//
//}
//
//void external_declar()
//{
//
//}
//
///*
//	<external_declar> ::= <type_specifier>(<TK_SEMICOLLON> 
//	| <declar><function body>
//	| <declar>[<TK_ASSIGN><initializer>]
//) 
//*/
//void translation_unit()
//{
//	while(token != TK_EOF)
//	{
//		external_declar();
//	}
//}
//
///*
//	<translation_unit> ::= {<external_declaration>}<TK_EOF>
//*/
//void parser(vector<Token> vec)
//{
//	translation_unit();
//}
//

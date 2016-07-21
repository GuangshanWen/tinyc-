
#ifndef __TOKEN__
#define __TOKEN__

#include<vector>
#include<string>
#include<map>
using namespace std;
enum Token
{
	TK_PLUS,//  "+"

	TK_MINUS,// "-"

	TK_STAR,// "*"

	TK_DIVID, // '/'

	TK_MOD, // '%'

	TK_EQ, // '=='

	TK_NEQ, // ' !='

	TK_LT, // '<'

	TK_LEQ , // '<='

	TK_GT, // '>'

	TK_GEQ, // '>='

	TK_ASSIGN,  // '='

	TK_POINTSTO, // '->'

	TK_DOT,   // '.'

	TK_AND, // '&'

	TK_OPENPA,  // '('

	TK_CLOSEPA, // ')'

	TK_OPENBR,  //  '['

	TK_CLOSEBR,  // ']'

	TK_BEGIN,    // '{'

	TK_END,   // '}'

	TK_SEMICOLON,   // ';'

	TK_COMMA,   // ','

	TK_ELLIPSIS, // '...'

	TK_EOF,  //  'end of file'
	 
	TK_CINT,  // 整型常量

	TK_CCHAR,  // 字符常量

	TK_CSTR,   // 字符串常量
	
	TK_CHAR,   //  char

	TK_SHORT,   //  short

	TK_INT,   //int

	TK_VOID,  // void

	TK_STRUCT,  // struct 

	TK_IF, // if

	TK_ELSE,  // else

	TK_FOR, // for

	TK_CONTINUE,  // continue

	TK_BREAK, // break

	TK_RETURN, // return 

	TK_SIZEOF, // sizeof 

	KW_ALLIGN,  // __align

	KW_CDECL, // __cdecl

	KW_STDCALL, // _stdcall


	TK_INDENT  // 标识符
};




#endif
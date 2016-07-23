
#ifndef __LEXER__
#define __LEXER__

#include<string>
#include <map>
#include "TOKEN.h"
#include <vector>
#include<iostream>
#include<fstream>
#include "error.h"
using namespace std;

struct Tokener{
	Token t;
	string s;
};

enum State{

	START,
	
	INDENT,
	COMMENT,

	CONST_NUM,
	CONST_STRING,
	CONST_CHAR,

	COMMENT_STAR
};
//extern vector<Tokener> Toker;
extern map<string,Token> key_symbol;

void init(ifstream&,string&);
void string_to_token(string &source,vector<Tokener>&);

//string TOKENER[TK_INDENT + 1];


#endif
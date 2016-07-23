
#ifndef __LEXER__
#define __LEXER__

#include<string>
#include <map>
#include "TOKEN.h"
#include <vector>
#include<iostream>
#include<fstream>

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

void init(ifstream&,string&);
void string_to_token(string &source,vector<Tokener>& Toker);

//string TOKENER[TK_INDENT + 1];


#endif

#ifndef __LEXER__
#define __LEXER__

#include<string>
#include <map>
#include "TOKEN.h"
#include <vector>
#include<iostream>
#include<fstream>

using namespace std;

void init(ifstream&,string&);


enum State{

	START,
	
	INDENT,
	COMMENT,

	CONST_NUM,
	CONST_STRING,
	CONST_CHAR,

};

struct Tokener{
	Token t;
	string s;
};


#endif

#include "lexer.h"
map<string,Token> key_symbol;
const int MAX_SIZE = 1024;
char buf[MAX_SIZE];

void init(ifstream &file,string&source_code)
{
	key_symbol["if"] = TK_IF;
	key_symbol["else"] = TK_ELSE;
	key_symbol["for"] = TK_FOR;
	key_symbol["break"] = TK_BREAK;
	key_symbol["continue"] = TK_CONTINUE;
	key_symbol["return"] = TK_RETURN;

	key_symbol["short"] = TK_SHORT;
	key_symbol["int"] = TK_INT;
	key_symbol["char"] = TK_CHAR;

	key_symbol["sizeof"] = TK_SIZEOF;
	key_symbol["void"] = TK_VOID;

	char *BUF;
	while(file.getline(buf , MAX_SIZE))
	{
		BUF = buf;
		while(*BUF){
			source_code += *BUF;
			BUF ++ ;
		}
		source_code += '\n';
	}
}


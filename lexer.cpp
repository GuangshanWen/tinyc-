#include"error.h"
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

	key_symbol["+"] = TK_PLUS;
	key_symbol["-"] = TK_MINUS;



	char *BUF;
	while(file.getline(buf , MAX_SIZE))
	{
		BUF = buf;
		while(*BUF){
			if(*BUF != ' ')source_code += *BUF;
			BUF ++ ;
		}
		source_code += '\n';
	}
}

void string_to_token(string &source,vector<Tokener>& Toker)
{
	int index = 0;
	string s = "";
	State state = START;
	Tokener Tmp;

	for(int i = 0; i < source.length(); ++i)
	{
		char c = source[i];
		
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		{
			switch(state)
			{
			case START:
				state = INDENT;
				break;
			case INDENT:
				state = INDENT;
				break;
			case COMMENT:
				state = COMMENT;
				break;
			case CONST_STRING:
				state = CONST_STRING;
				break;
			case CONST_CHAR:
				if(source[i+1] != '\'')
				{}
				else
					state = START;
				break;
			}
		}

		else if(c >= '0' && c <= '9')
		{
			switch (state)
			{
			case START :
				state = CONST_NUM;
				s += c;
				break;
			case INDENT :
				state = INDENT;
				s += c;
				break;
			case COMMENT :
				state = COMMENT;
				break;
			case COMMENT_STAR:
				state = COMMENT_STAR;
				break;
			case CONST_STRING :
				state = CONST_STRING;
				s += c;
				break;
			case CONST_NUM :
				state = CONST_NUM;
			case CONST_CHAR :
				if(source[i+1] != '\''){}
				else{
					state = START;
					s += c;
				}
				break;
			}
		}

		else if(c == '\n')
		{
			switch (state)
			{
			case COMMENT_STAR:
				state = COMMENT_STAR;
				break;
			case COMMENT:
				state = START;
				break;
			default:
				error();
				// something wrong!
			}
		}

		else if(c == '+' || c == '-') // 不支持 ++， --
		{
			switch (state)
			{
			case START :
				s += c;

				Tmp.s = s;
				c == '+'?Tmp.t = TK_PLUS:Tmp.t = TK_MINUS;

				Toker.push_back(Tmp);

				state = START;
				s = "";

				break;
				
			case COMMENT:
				break;
			case COMMENT_STAR:
				break;
				
			case INDENT :
				Tmp.s = s;
				Tmp.t = (key_symbol[s] ? key_symbol[s]:TK_INDENT);
				
				Toker.push_back(Tmp);

				i--;
				s = "";
				state = START;

				break;

			case CONST_STRING :
				state = CONST_STRING;
				s += c;
				break;
				
			case CONST_CHAR:
				if(source[i + 1] != '\'')
				{}
				else
				{
					Tmp.s = c;
					Tmp.t = TK_CCHAR;

					Toker.push_back(Tmp);

					i++;
					s = "";
					state = START;
				}
				break;
			case CONST_NUM:
				error();
				break;
			}
		}
		else if(c == '/')
		{
			if(source[i+1] == '*'){
				switch(state)
				{
				case INDENT: 
					Tmp.s = s;
					Tmp.t = (key_symbol[s]?key_symbol[s] : TK_INDENT);
					break;
					
				case COMMENT: COMMTN_STAR:
					continue;

				case CONST_STRING:
					s += c;
					continue;
					
				case CONST_CHAR :
					error();
					
				}

				state = COMMENT_STAR;
				i++;
				continue;
			}
			else if(source[i + 1] == '/')
			{
				switch(state)
				{
				case INDENT: 
					Tmp.s = s;
					Tmp.t = (key_symbol[s]?key_symbol[s] : TK_INDENT);
					break;
					
				case COMMENT: COMMTN_STAR:
					continue;

				case CONST_STRING:
					s += c;
					continue;
					
				case CONST_CHAR :
					error();
					continue;
				}
				state = COMMENT;
				i++;
				continue;

			}
		    switch(state) //不是注释
			{
			case START :
				Tmp.s = (s+=c);
				Tmp.t = TK_DIVID;

				s = "";
				state = START;
				Toker.push_back(Tmp);
				break;
				
			case INDENT:
				Tmp.s = (s);
				Tmp.t = (key_symbol[s]?key_symbol[s]:TK_INDENT);

				Toker.push_back(Tmp);
				state = START;
				i--;
				break;

			case COMMENT: COMMTN_STAR:
					continue;

			case CONST_STRING:
					s += c;
					continue;
					
			case CONST_CHAR :
				if(source[i+1] != ' ')
					error();
				Tmp.s = (s+=c);
				Tmp.t = TK_CCHAR;

				s = "";
				state = START;
				i++;
				break;
				
			case CONST_NUM :
				state = START;
				i--;
				
				Tmp.s = s;
				Tmp.t = TK_CINT;

				s = "";
				break;
			}
		}
		else if( c == '*')
		{
			if(source[i+1] == '/')
			{
				state = START;
				s = "";
				i++;
				continue;
			}
			else
			{
				switch(state)
				{
				case START:
					Tmp.s = (s+=c);
					Tmp.t = TK_STAR;
					break;

				case INDENT:
					Tmp.s = s;
					Tmp.t = (key_symbol[s]?key_symbol[s]:TK_INDENT);

					s = "";
					i--;
					break;

				case COMMENT: COMMENT_STAR:
					break;

				case CONST_STRING :
					s += c;
					break;

				case CONST_CHAR:
					if(source[i + 1]!= '\'')
						error();
					i++;
					Tmp.s = (s += c);
					Tmp.t = TK_CCHAR;

					Toker.push_back(Tmp);

					s = "";
					state = START;
					break;

				case CONST_NUM:
					Tmp.s = (s);
					Tmp.t = TK_CINT;

					Toker.push_back(Tmp);

					s = "";
					i--;
					state = START;

					break;
				}
			}
		{
	}
}
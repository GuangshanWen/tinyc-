#include"error.h"
#include "lexer.h"

map<string,Token> key_symbol;
map<string,Token> Fin;

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
	key_symbol["struct"] = TK_STRUCT;

	Fin["{"] = TK_BEGIN;
	Fin["}"] = TK_END;
	Fin["["] = TK_OPENBR;
	Fin["]"] = TK_CLOSEBR;
	Fin["("] = TK_OPENPA;
	Fin[")"] = TK_CLOSEPA; 
	Fin[";"] = TK_SEMICOLON;
	Fin[","] = TK_COMMA;
	Fin["%"] = TK_MOD;
	Fin["&"] = TK_AND;

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

void string_to_token(string &source,vector<Tokener>&Toker)
{
	int index = 0;
	string s = "";
	State state = START;
	Tokener Tmp;

	for(size_t i = 0; i < source.length(); ++i)
	{
		char c = source[i];
		
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
		{
			switch(state)
			{
			case START:
				s += c;
				state = INDENT;
				break;

			case CONST_NUM:
				error("letter in num");

			case INDENT:
				s += c;
				state = INDENT;
				break;

			case COMMENT:case COMMENT_STAR:
				
				break;

			case CONST_STRING:
				state = CONST_STRING;
				s += c;
				break;

			case CONST_CHAR:
				if(source[i+1] != '\'')
					error("illegal char");
				else{
					Tmp.s = (s+c);
					Tmp.t = TK_CINT;
					i++;
					s = "";
					state = START;
				}
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
				break;
			case CONST_CHAR :
				if(source[i+1] != '\'')
					error("illegal char");
				else{
					state = START;
					Tmp.s = (s += c);
					Tmp.t = TK_CCHAR;

					i++;
					Toker.push_back(Tmp);
					s = "";
					state = START;
				}
				break;
			}
		}

		else if(c == '\n')
		{
			switch (state)
			{
			case START :
			case INDENT:
				Tmp.s = s;
				Tmp.t = TK_INDENT;

				Toker.push_back(Tmp);
				s = "";
				state = START;
				break;
			case COMMENT_STAR:
				state = COMMENT_STAR;
				break;
			case COMMENT:
				state = START;
				break;
			case CONST_STRING:
			case CONST_CHAR:
			case CONST_NUM:
				error("缺少分号");
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
					error("谁能告诉我这是为什么");
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
				Tmp.s = s;
				Tmp.t = TK_CINT;
				
				Toker.push_back(Tmp);

				i--;
				s = "";
				state = START;
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

					Toker.push_back(Tmp);
					break;
					
				case COMMENT: case COMMENT_STAR:
					continue;

				case CONST_STRING:
					s += c;
					continue;
					
				case CONST_CHAR :
					error("真是莫名其妙啊");
				}

				state = COMMENT_STAR;
				i++;
				s = "";
				continue;
			}
			else if(source[i + 1] == '/')
			{
				switch(state)
				{
				case INDENT: 
					Tmp.s = s;
					Tmp.t = (key_symbol[s]?key_symbol[s] : TK_INDENT);

					Toker.push_back(Tmp);
					break;
					
				case COMMENT: case COMMENT_STAR:
					continue;

				case CONST_STRING:
					s += c;
					continue;
					
				case CONST_CHAR :
					error("龙日天这个傻逼");
					continue;
				}
				state = COMMENT;
				i++;
				s = "";
				continue;

			}
		    switch(state) //不是注释
			{
			case START :
				Tmp.s = (s+=c);
				Tmp.t = TK_DIVIDE;

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
				s = "";
				break;

			case COMMENT: case COMMENT_STAR:
					continue;

			case CONST_STRING:
					s += c;
					continue;
					
			case CONST_CHAR :
				if(source[i+1] != ' ')
					error("实验室真是挫");
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
				switch(state)
				{
				case COMMENT_STAR:
					state = START;
					i++;
					break;
				case COMMENT:
					break;
				default:
					error("1");
				}
				continue;
			}
			else
			{
				switch(state)
				{
				case START:
					Tmp.s = (s+=c);
					Tmp.t = TK_STAR;

					Toker.push_back(Tmp);
					s = "";
					state = START;

					break;

				case INDENT:
					Tmp.s = s;
					Tmp.t = (key_symbol[s]?key_symbol[s]:TK_INDENT);

					Toker.push_back(Tmp);
					s = "";
					i--;
					state = START;
					break;

				case COMMENT: case COMMENT_STAR:
					break;

				case CONST_STRING :
					s += c;
					break;

				case CONST_CHAR:
					if(source[i + 1]!= '\'')
						error("z");
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
		}

		else if(c == '<' || c == '>')
		{
			switch(state)
			{
			case START:
				s = s+c;
				if(source[i+1] == '=')
				{
					s = s + '=';
					Tmp.t = (c == '<'?TK_LEQ:TK_GEQ);
					i++;
				}
				else Tmp.t = (c == '<'?TK_LT:TK_GT);

				Tmp.s = s;
				Toker.push_back(Tmp);

				s = "";
				state = START;
				
				break;

			case INDENT:
				Tmp.s = s;
				Tmp.t = (key_symbol[s]?key_symbol[s] : TK_INDENT);

				Toker.push_back(Tmp);
				s = "";
				i--;
				state = START;
				break;

			case COMMENT: case COMMENT_STAR:
				break;
			case CONST_STRING:
				s+=c;
				break;

			case CONST_CHAR:
				if(source[i+1] != '\'')
					error("???");
				i++;
				s = s + c;
				Tmp.s = s;
				Tmp.t = TK_CCHAR;
				
				s = "";
				state = START;
				break;

			case CONST_NUM:
				Tmp.s = s;
				Tmp.t = TK_CINT;

				Toker.push_back(Tmp);

				i--;
				s = "";
				state = START;
				break;
			}
		}

		else if(c == '=')
		{
			switch(state)
			{
			case START:
				if(source[i+1] == '=')
				{
					Tmp.s = "==";
					Tmp.t = TK_EQ;
					i++;
				}
				else
				{
					Tmp.s = "=";
					Tmp.t = TK_ASSIGN;
				}

				Toker.push_back(Tmp);
				s = "";
				state = START;
				
				break;

			case COMMENT:case COMMENT_STAR:
				break;
			case CONST_STRING :
				s += c;
				break;
			case CONST_CHAR:
				if(source[i+1] != '\'')
					error("''''");
				i++;
				Tmp.s = (s += c);
				Tmp.t = TK_CCHAR;

				Toker.push_back(Tmp);
				
				s = "";
				state = START;
				break;

			case CONST_NUM :
				Tmp.s = s;
				Tmp.t = TK_CINT;
				
				Toker.push_back(Tmp);

				s = "";
				state = START;
				i--;

				break;
			case INDENT:
				Tmp.s = s;
				Tmp.t = (key_symbol[s] ? key_symbol[s] : TK_INDENT);

				Toker.push_back(Tmp);

				i--;
				state = START;
				s = "";
				break;
			}
		}
		else if(c == '{' || c == '}' || c == '[' || c == ']' || \
			    c == '(' || c == ')' || c == ';' || c == '&' || c == '%' || c == ','\
			    )
		{
			switch(state)
			{
			case START : 
				s += c;
				Tmp.s = s;
				Tmp.t = Fin[s];

				Toker.push_back(Tmp);

				s = "";
				state = START;
				break;

			case INDENT:
				Tmp.s = s;
				Tmp.t = (key_symbol[s]?key_symbol[s]:TK_INDENT);

				Toker.push_back(Tmp);

				s = "";
				state = START;
				i--;
				break;

			case COMMENT:case COMMENT_STAR:
				break;

			case CONST_NUM:
				Tmp.s = s;
				Tmp.t = TK_CINT;

				Toker.push_back(Tmp);

				s = "";
				state = START;
				i--;
				break;

			case CONST_CHAR:
				if(source[i+1]!= '\'')
					error("illegal char");
				Tmp.s = (s+=c);
				Tmp.t = TK_CCHAR;

				s = "";
				state = START;
				i++;
				break;

			case CONST_STRING :
				s += c;
				break;
			}
		}

		else if(c == '\'')
		{
			switch(state)
			{
			case START:
				state = CONST_CHAR;
				break;
			case COMMENT: case COMMENT_STAR:
				break;
			case CONST_STRING:
				s+=c;
				break;
			default:
				error("1");
			}
		}

		else if(c == '!')
		{
			if(source[i+1] != '=' && state != CONST_CHAR && state != CONST_STRING)
				error("2");

			switch(state)
			{
			case (START):
				break;
			case COMMENT_STAR:case COMMENT:
				continue;

			case CONST_STRING:
				s += c ;
				continue;

			case CONST_NUM:
				Tmp.s = s;
				Tmp.t = TK_CINT;

				Toker.push_back(Tmp);

				s = "";
				break;
			case INDENT:
				Tmp.s = s;
				Tmp.t = (key_symbol[s]?key_symbol[s]:TK_INDENT);

				Toker.push_back(Tmp);

				break;
			}

			if(state != CONST_CHAR)
			{
				Tmp.s = "!=";
				Tmp.t = TK_NEQ;
				i++;
				Toker.push_back(Tmp);
				s = "";
				state = START;
				continue;
			}
			else if(state == CONST_CHAR)
			{
				Tmp.s = "!";
				Tmp.t = TK_CCHAR;

				Toker.push_back(Tmp);

				s = "";
				state = START;
				i++;
				continue;
			}
		}
		else if(c == '"')
		{
			switch(state)
			{
			case START:
				state = CONST_STRING;
				break;
			case CONST_STRING :
				Tmp.s = s;
				Tmp.t = TK_CSTR;

				Toker.push_back(Tmp);

				s = "";
				state = START;
				break;
			case INDENT:case CONST_NUM:
				error("4");
			case CONST_CHAR:
				if(source[i+1]!= '\'')
					error("3");
				Tmp.s = '"';
				Tmp.t = TK_CCHAR;

				Toker.push_back(Tmp);

				i++;
				state = START;
				s = "";
				break;

			case COMMENT:
			case COMMENT_STAR:
				break;
			}
		}

		else if(c == ' ')
		{
			switch(state)
			{
			case START:
			case COMMENT :
			case COMMENT_STAR:
				break;
			case CONST_STRING :
				s += c;
				break;
			case CONST_NUM:
				Tmp.s = s;
				Tmp.t = TK_CINT;

				Toker.push_back(Tmp);
				s = "";
				state = START;
				break;

			case CONST_CHAR:
				if(source[i + 1]!='\'')
				{
					error("illegal char");
				}
				i++;
				Tmp.s = (s+' ');
				Tmp.t = TK_CCHAR;

				Toker.push_back(Tmp);
				state = START;
				s = "";
				break;

			case INDENT:
				Tmp.s = s;
				Tmp.t = (key_symbol[s]? key_symbol[s] : TK_INDENT);

				Toker.push_back(Tmp);
				state = START;
				s = "";
				break;
			}
		}
	}

	Tmp.s = "End Of File";
	Tmp.t = TK_EOF;

	Toker.push_back(Tmp);
}
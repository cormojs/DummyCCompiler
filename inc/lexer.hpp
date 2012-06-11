#ifndef LEXER_HPP
#define LEXER_HPP
	
#include<llvm/Support/raw_ostream.h>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<map>
#include<fstream>
#include<vector>
#include<list>
#include"APP.hpp"


/**
  * トークン種別
  */
enum TokenType{
	TOK_IDENTIFIER,	//識別子
	TOK_STRING,			//文字列
	TOK_DIGIT,			//数字
	TOK_SYMBOL,			//記号
	TOK_INT,				//INT
	TOK_IF,				//IF
	TOK_ELSE,			//ELSE
	TOK_WHILE,			//WHILE
	TOK_CONTINUE,		//CONTINUE
	TOK_BREAK,			//BREAK
	TOK_RETURN,			//RETURN
	TOK_EOF				//EOF
};

/**
  * 変数種別
  */
enum ValType{
	TYPE_INT,
	//TYPE_CHAR
};


/**
  *個別トークン格納クラス
  */
typedef class Token{
	public:

	private:
	TokenType Type;
	std::string TokenString;
	int Number;
	int Line;


	public:
	Token(std::string string, TokenType type, int line) 
		: TokenString(string), Type(type), Line(line){
		if(type == TOK_DIGIT)
			Number = atoi(string.c_str());
		else
			Number = 0x7fffffff;
	};
	~Token(){};


	TokenType getTokenType(){return Type;};
	std::string getTokenString(){return TokenString;};
	int getNumberValue(){return Number;};
	bool setLine(int line){Line=line;return true;}
	int getLine(){return Line;}
	
}Token;



/**
  * 切り出したToken格納用クラス
  */
class TokenSet{
	public:

	private:
		std::vector<Token*> Tokens;
		int CurIndex;

	protected:

	public:
		TokenSet():CurIndex(0){}
		~TokenSet();


		bool ungetToken(int Times=1);
		bool getNextToken();
		bool pushToken(Token *token){
			Tokens.push_back(token);
			return true;
		}
		Token getToken();
		TokenType getCurType(){return Tokens[CurIndex]->getTokenType();}
		std::string getCurString(){return Tokens[CurIndex]->getTokenString();}
		int getCurNumVal(){return Tokens[CurIndex]->getNumberValue();}
		bool printTokens();
		int getCurIndex(){return CurIndex;}
		bool applyTokenIndex(int index){CurIndex=index;return true;}
		
		

	private:

	protected:


};

TokenSet *LexicalAnalysis(std::string input_filename);
#endif
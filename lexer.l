%{
#include <string>
#include "tree.hpp"
#include "parser.hpp"

#define SAVE_STRING yylval.id = new std::string(yytext, yyleng)
#define NUMB yylval.number = std::stod(std::string(yytext,yyleng))

extern "C" int yywrap() { return 1;}
%}

%%

[ \t\n]                 ;
"//".*\n               ;
"IF" { return IF;}
"ELSE" {  return ELSE;}
"WHILE" { return WHILE;}
"PRINT" { return PRINT;}
"RETURN" { return RETURN;}
[a-zA-z][a-zA-Z0-9]*   SAVE_STRING; return ID;
[0-9]+                 NUMB; return NUMBER;
"(" {return LPAREN;}
")" {return RPAREN;}
"{" {return CLPAREN;}
"}" { return CRPAREN;}
";" { return SEMICOLON;}
"+" { return PLUS;}
"-" { return MINUS;}
"*" { return TIMES;}
"/" { return DIVIDE;}
"=" { return ASSIGN;}
"==" { return EQ;}
"!=" { return NEQ;}
"<" { return LT;}
">" { return GT;}
"<=" { return LEQ;}
">=" { return GEQ;}
"," { return COMMA;}
%%

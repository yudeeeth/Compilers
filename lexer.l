%{
#include <string>
#include <iostream>
#include "tree.hpp"
#include "parser.hpp"

#define SAVE_STRING yylval.id = new std::string(yytext, yyleng)
#define NUMB yylval.number = std::stod(std::string(yytext,yyleng))

extern "C" int yywrap() { return 1;}
%}

%%

[\t ]                    ;
\n {yylineno++;}      ;
":"  {return SLASHN;}
"//".*\n               ;
"ORUVELA" { return IF;}
"ILLENA" {  return ELSE;}
"WHILE" { return WHILE;}
"FOR" { return FOR;}
"VECHUKO" { return VECHUKO; }
"SOLRAN" { return SOLRAN; }
"SEIRAN" { return SEIRAN; }
"NA" { return NA; }
"VAATI SONNA" { return VAATI_SONNA; }
"VAATI SONNA MAARI" { return SONNA_MAARI; }
"ITHU EPDI IRUKU" { return RETURN;}
"BREAK" {return BREAK;}
"CONTINUE" {return CONTINUE;}
"IN" {return IN;}
"\"".*"\"" { SAVE_STRING; return STRING;}
KANNA_[a-zA-Z][a-zA-Z0-9]*   { SAVE_STRING; return ID; }
[0-9]+                 NUMB; return NUMBER;
"(" {return LPAREN;}
")" {return RPAREN;}
"{" {return CLPAREN;}
"}" { return CRPAREN;}
"[" { return SLPAREN;}
"]" { return SRPAREN;}
"++" { return INC;}
"--" { return DEC;}
"+" { return PLUS;}
"%" { return MOD;}
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

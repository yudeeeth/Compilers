#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "context.hpp"
#include <string.h>
#include "tree.hpp"
extern int yyparse();
extern FILE *yyin;
// extern YYSTYPE yylval;
std::vector<std::unordered_map<std::string,double>> ec;
get_exec_context exec_context(ec);
std::unordered_map<std::string,func_def> func_table;
bool GLOBALreturned=false;
double GLOBALretval=0;

int enteredLoop = 0;
bool breakSet = false;
bool continueSet = false;
int labelcount=0;
unordered_set<string> decl;
bool mode = true;

int main(int argc, char **argv) {
  FILE *fp = stdin;
  if (argc >= 2) {
    fp = fopen(argv[1], "r");
  }
  if(argc == 3)
    mode = strcmp(argv[2],"true")==0?true:false;
  yyin = fp;
  yyparse();
  return 0;
}

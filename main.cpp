#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "context.hpp"
#include "tree.hpp"
extern int yyparse();
extern FILE *yyin;
// extern YYSTYPE yylval;
std::vector<std::unordered_map<std::string,double>> ec;
get_exec_context exec_context(ec);
std::unordered_map<std::string,func_def> func_table;

int main(int argc, char **argv) {
  FILE *fp = stdin;
  if (argc >= 2) {
    fp = fopen(argv[1], "r");
  }
  yyin = fp;
  yyparse();
  // std::cout << exps.size();
  return 0;
}

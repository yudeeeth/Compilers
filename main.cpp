#include <iostream>
#include <string>

#include <unordered_map>
extern int yyparse();
extern FILE *yyin;
// extern YYSTYPE yylval;
std::unordered_map<std::string,double> exec_context;


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

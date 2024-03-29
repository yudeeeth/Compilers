%{
    #include "tree.hpp"
    #include <string>
    #include <vector>
    #include <unordered_map>

    extern int yylex();
    extern bool mode;
    extern int yylineno, yychar;
    void yyerror(const char *s) { fprintf(stderr,
"%s: token %d near line %d\n",
s, yychar, yylineno);}
%}


/* Represents the many different ways we can access our data */
%union {
    treenode *td;
    double number;
    std::string* id;
}

/* Define terminals */

%token <number> NUMBER
// identifier
%token <id> ID
%token <id> STRING
// operators
%token PLUS
%token MINUS
%token TIMES
%token DIVIDE
%token MOD
%token ASSIGN
%token INC
%token DEC

%token NEQ
%token EQ
%token LT
%token GT
%token LEQ
%token GEQ

// miscellaneous
/* %token COMMA */
%token CLPAREN
%token CRPAREN
%token LPAREN
%token RPAREN
%token SLPAREN
%token SRPAREN
%token SLASHN
%token COMMA

//keywords
%token IF
%token ELSE
%token WHILE
%token VECHUKO
%token RETURN
%token FOR
%token IN
%token BREAK
%token CONTINUE
%token SOLRAN
%token SEIRAN
%token NA
%token VAATI_SONNA
%token SONNA_MAARI
/* %token RETURN
%token FUNCTION */
%type <td> program
%type <td> expression
%type <td> statements statement
%type <td> operator
%type <td> comparison 
%type <td> args
%type <td> params
%type <td> unary

%start program

%%
program : statements { treenode * toplevel = new treenode(NODE_STATEMENTS,$1);
                    if(mode)
                      toplevel->compile();
                    else
                      toplevel->execute();
                    // cout<<"interpreter starts from here:"<<endl;
                    // toplevel->execute();
                    };
statements : statement statements {$$ = new treenode(NODE_STATEMENTS,$1,$2);}
            | statement { $$ = new treenode(NODE_STATEMENTS,$1); }
            ;
statement : ID SLASHN { $$ = new treenode(NODE_DECLARE, *($1)); }
          | ID SLPAREN expression SRPAREN SLASHN { $$ = new treenode(NODE_DECLARE, *($1), $3); }
          | expression SOLRAN ID SEIRAN SLASHN   { $$ = new treenode(NODE_ASSIGN,*($3),$1); }
          | expression SOLRAN ID SLPAREN expression SRPAREN SEIRAN SLASHN { $$ = new treenode(NODE_ASSIGN,*($3),$1,$5); }
          | expression SLASHN { $$ = new treenode(NODE_EXPR,$1); }
          | IF LPAREN expression RPAREN CLPAREN statements CRPAREN ELSE CLPAREN statements CRPAREN { 
            $$ = new treenode(NODE_IFELSE,$3,$6,$10);
          }
          | IF LPAREN expression RPAREN CLPAREN statements CRPAREN ELSE statement { 
            $$ = new treenode(NODE_IFELSE,$3,$6,$9);
          }
          | IF LPAREN expression RPAREN statement ELSE statement { 
            $$ = new treenode(NODE_IFELSE,$3,$5,$7);
          }
          | IF LPAREN expression RPAREN statement ELSE CLPAREN statements CRPAREN { 
            $$ = new treenode(NODE_IFELSE,$3,$5,$8);
          }
          | IF LPAREN expression RPAREN CLPAREN statements CRPAREN {
            $$ = new treenode(NODE_IF,$3,$6);
          }
          | IF LPAREN expression RPAREN statement {
            $$ = new treenode(NODE_IF,$3,$5);
          }
          | WHILE LPAREN expression RPAREN CLPAREN statements CRPAREN {
            $$ = new treenode(NODE_WHILE,$3,$6);
          }
          | WHILE LPAREN expression RPAREN statement {
            $$ = new treenode(NODE_WHILE,$3,$5);
          }
          | NA LPAREN statement RPAREN VAATI_SONNA LPAREN statement RPAREN SONNA_MAARI LPAREN statement RPAREN CLPAREN statements CRPAREN {
            $$ = new treenode(NODE_FOR,$3,$7,$11,$14);
          }
          | VECHUKO LPAREN STRING RPAREN SLASHN {
            $$ = new treenode(NODE_PRINT,*($3));
          }
          | VECHUKO LPAREN expression RPAREN SLASHN {
            $$ = new treenode(NODE_PRINT, $3);
          }
          | ID LPAREN RPAREN CLPAREN statements CRPAREN {
            $$ = new treenode(NODE_FUNC,*($1),NULL,$5);
          }
          | ID LPAREN args RPAREN CLPAREN statements CRPAREN {
            $$ = new treenode(NODE_FUNC,*($1),$3,$6);
          }
          | RETURN expression SLASHN {
            $$ = new treenode(NODE_RETURN,$2);
            // cout<<"---->"<<$2->execute()<<endl;
          }
          | IN LPAREN ID RPAREN SLASHN {
            $$ = new treenode(NODE_IN,*($3));
          }
          | BREAK SLASHN {
            $$ = new treenode(NODE_BREAK);
          }
          | CONTINUE SLASHN {
            $$ = new treenode(NODE_CONTINUE);
          }
          | ID SLPAREN SRPAREN LPAREN expression RPAREN SLASHN {
            $$ = new treenode(NODE_DECLARE,*($1),$5);
          } 
          | ID SLPAREN SRPAREN SLPAREN args SRPAREN SLASHN {
            $$ = new treenode(NODE_ARR,*($1),$5);
          } 
          ;
args      : expression COMMA args {
            $$ = new treenode(NODE_ARGS,$1,$3);
          }
          |  expression { 
            $$ = new treenode(NODE_ARGS,$1);
          }
          ;
params   : ID COMMA params {
            $$ = new treenode(NODE_PARAM,*($1),$3);
          }
          | ID {
            $$ = new treenode(NODE_PARAM,*($1));
          }
          ; 
expression : expression operator expression { 
              $$ = new treenode(NODE_OPER,$1,$2,$3);
           }
           | expression comparison expression {
              $$ = new treenode(NODE_COMP,$1,$2,$3);
           }
           | ID SLPAREN expression SRPAREN {
              $$ = new treenode(NODE_ID,*($1),$3);
           }
           | ID unary {
              $$ = new treenode(NODE_OPER,*($1),$2);
           }
           | LPAREN expression RPAREN { $$ = new treenode(NODE_EXPR, $2); }
           | ID { $$ = new treenode(NODE_ID,(string) *($1)); }
           | NUMBER { $$ = new treenode(NODE_VAL,$1); }
          | ID LPAREN RPAREN{
            $$ = new treenode(NODE_CALL,*($1),NULL);
          }
          | ID LPAREN args RPAREN{
            $$ = new treenode(NODE_CALL,*($1),$3);
          }
          ;
comparison: EQ {$$ = new treenode  (NODE_COMP,(string)"==");}
          | NEQ {$$ = new treenode (NODE_COMP,(string)"!=");}
          | LT {$$ = new treenode  (NODE_COMP,(string)"<" );}
          | GT {$$ = new treenode  (NODE_COMP,(string)">" );}
          | LEQ {$$ = new treenode (NODE_COMP,(string)"<=");}
          | GEQ {$$ = new treenode (NODE_COMP,(string)">=");}
          ;
operator: PLUS { $$ = new treenode (NODE_OPER,(string)"+" );}
        | MINUS { $$ = new treenode(NODE_OPER,(string)"-" );}
        | TIMES { $$ = new treenode(NODE_OPER,(string)"*" );}
        | DIVIDE {$$ = new treenode(NODE_OPER,(string)"/" );}
        | MOD {$$ = new treenode(NODE_OPER,(string)"%" );}
        ;
unary   : INC { $$ = new treenode(NODE_OPER,(string)"++");}
        | DEC { $$ = new treenode(NODE_OPER,(string)"--");}
        ;
%%

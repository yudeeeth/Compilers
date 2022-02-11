%{
    #include "tree.hpp"
    #include <string>
    #include <vector>
    #include <unordered_map>

    #define NODE_STATEMENTS 2356534
    #define NODE_IF 572456
    #define NODE_IFELSE 574655
    #define NODE_WHILE 573346
    #define NODE_ASSIGN 345645
    #define NODE_DECLARE 345765
    #define NODE_EXPR 235655
    #define NODE_PRINT 345745
    #define NODE_OPER 736423
    #define NODE_COMP 236474
    #define NODE_ID 8902783
    #define NODE_VAL 489392
    #define NODE_FUNC 908987
    #define NODE_PARAM 908122
    #define NODE_CALL 909824
    #define NODE_ARGS 8787878
    #define NODE_RETURN 345345
    #define NODE_IN 201902

    extern int yylex();
    extern int yylineno, yychar;
    void yyerror(const char *s) { fprintf(stderr,
"%s: token %d on line %d\n",
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
%token NEQ
%token EQ
%token LT
%token GT
%token LEQ
%token GEQ

// missellaneous
/* %token COMMA */
%token CLPAREN
%token CRPAREN
%token LPAREN
%token RPAREN
%token SEMICOLON
%token COMMA

//keywords
%token IF
%token ELSE
%token WHILE
%token PRINT
%token RETURN
%token IN
/* %token RETURN
%token FUNCTION */
%type <td> program
%type <td> expression
%type <td> statements statement
%type <td> operator
%type <td> comparison 
%type <td> args
%type <td> params

%start program

%%
program : statements { treenode * toplevel = new treenode(NODE_STATEMENTS,$1);
                    toplevel->execute();
                    };
statements : statement statements {$$ = new treenode(NODE_STATEMENTS,$1,$2);}
            | statement { $$ = new treenode(NODE_STATEMENTS,$1); }
            ;
statement : ID SEMICOLON { $$ = new treenode(NODE_DECLARE, *($1)); }
          | ID ASSIGN expression SEMICOLON { $$ = new treenode(NODE_ASSIGN,*($1),$3); }
          | expression SEMICOLON { $$ = new treenode(NODE_EXPR,$1); }
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
          | PRINT LPAREN STRING RPAREN SEMICOLON {
            $$ = new treenode(NODE_PRINT,*($3));
          }
          | PRINT LPAREN expression RPAREN SEMICOLON {
            $$ = new treenode(NODE_PRINT, $3);
          }
          | ID LPAREN RPAREN CLPAREN statements CRPAREN {
            $$ = new treenode(NODE_FUNC,*($1),NULL,$5);
          }
          | ID LPAREN args RPAREN CLPAREN statements CRPAREN {
            $$ = new treenode(NODE_FUNC,*($1),$3,$6);
          }
          | RETURN expression SEMICOLON {
            $$ = new treenode(NODE_RETURN,$2);
            // cout<<"---->"<<$2->execute()<<endl;
          }
          | IN LPAREN ID RPAREN SEMICOLON {
            $$ = new treenode(NODE_IN,*($3));
          }
          | error SEMICOLON 
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
%%

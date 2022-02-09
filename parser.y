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

    extern int yylex();
    void yyerror(const char *s) { printf("ERROR: %sn", s); }
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
// operators
%token PLUS
%token MINUS
%token TIMES
%token DIVIDE
%token ASSIGN
%token NEQ
%token EQ
%token LT
%token GT
%token LEQ
%token GEQ

// missellaneous
%token CLPAREN
%token CRPAREN
%token LPAREN
%token RPAREN
%token SEMICOLON

//keywords
%token IF
%token ELSE
%token WHILE
%token PRINT
/* %token RETURN
%token FUNCTION */
%type <td> program
%type <td> expression
%type <td> statements statement
%type <td> operator
%type <td> comparison 

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
          | IF LPAREN expression RPAREN CLPAREN statements CRPAREN {
            $$ = new treenode(NODE_IF,$3,$6);
          }
          | WHILE LPAREN expression RPAREN CLPAREN statements CRPAREN {
            $$ = new treenode(NODE_WHILE,$3,$6);
          }
          | PRINT LPAREN expression RPAREN SEMICOLON {
            $$ = new treenode(NODE_PRINT,$3);
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
        ;
%%

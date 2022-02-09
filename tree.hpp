#pragma once
#include <iostream>
#include <string>
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
using namespace std;
extern unordered_map<string, double> exec_context;
class treenode{
  public:
      treenode *first,*second,*third;
      int type;
      double value;
      string symbol;
      treenode(int code, treenode * _first=NULL, treenode* _second =NULL, treenode * _third=NULL){
        type = code;
        first = _first;
        second = _second;
        third = _third;
      }
      treenode(int code, string _symbol, treenode* _first = NULL){
        type = code;
        symbol = _symbol;
        first = _first;
      }
      treenode(int code, double val){
        type = code;
        value = val;
        first = NULL;
        second = NULL;
        third = NULL;
      }
      
      int execute(){
        switch(type){
          case NODE_STATEMENTS:
            first->execute();
            if(second!=NULL)
              second->execute();
            break;
          case NODE_IF:
            if((int)first->execute()){
              second->execute();
            }
            break;
          case NODE_IFELSE:
            if((int)first->execute()){
              second->execute();
            }else{
              third->execute();
            }
            break;
          case NODE_WHILE:
            while((int)first->execute()){
              second->execute();
            }
            break;
          case NODE_ASSIGN:
            if(exec_context.count(symbol)!=0)
              exec_context[symbol] = first->execute();
            return exec_context[symbol];
            break;
          case NODE_DECLARE:
            if(exec_context.count(symbol)==0)
              exec_context[symbol] = 0;
            break;
          case NODE_EXPR:
            return first->execute();
            break;
          case NODE_PRINT:
            cout << first->execute() << endl;
            break;
          case NODE_OPER:
            if(second->symbol=="+"){
              return first->execute() + third->execute();
            }
            else if (second->symbol=="-"){
              return first->execute() - third->execute();
            }
            else if(second->symbol=="*"){
              return first->execute() * third->execute();
            }
            else if (second->symbol=="/"){
              return first->execute() / third->execute();
            }
            break;
          case NODE_COMP:
            if(second->symbol=="=="){
              return first->execute() == third->execute();
            }
            else if (second->symbol=="!="){
              return first->execute() != third->execute();
            }
            else if(second->symbol=="<"){
              return first->execute() < third->execute();
            }
            else if (second->symbol==">"){
              return first->execute() > third->execute();
            }
            else if(second->symbol=="<="){
              return first->execute() <= third->execute();
            }
            else if (second->symbol==">="){
              return first->execute() >= third->execute();
            }
            break;
          case NODE_ID:
            return exec_context[symbol];
            break;
          case NODE_VAL:
            return value;
        }
      }


    };
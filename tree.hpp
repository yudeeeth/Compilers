#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "context.hpp"
#include "funcdef.hpp"
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

using namespace std;

extern double GLOBALretval;
extern bool GLOBALreturned;
extern get_exec_context exec_context;
extern unordered_map<string,func_def> func_table;
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
      treenode(int code, string _symbol, treenode* _first = NULL,treenode* _second = NULL){
        type = code;
        symbol = _symbol;
        first = _first;
        second = _second;
      }
      treenode(int code, double val){
        type = code;
        value = val;
        first = NULL;
        second = NULL;
        third = NULL;
      }

      void helperlist(vector<double> & li){
        li.push_back(first->execute());
        if(second!=NULL){
          second->helperlist(li);
        }
      }

      vector<double> list(){
        vector<double> sol;
        sol.push_back(first->execute());
        if(second!=NULL){
          second->helperlist(sol);
        }
        return sol;
      }

      void helperplist(vector<string> &li){
        li.push_back(first->symbol);
        if(second!=NULL){
          second->helperplist(li);
        }
      }

      vector<string> plist(){
        vector<string> sol;
        // cout<<"plist"<<endl;
        sol.push_back(first->symbol);
        // cout<<"first->first->symbol"<<endl;
        if(second!=NULL){
          second->helperplist(sol);
        }
        return sol;
      }
      
      void printnodes(){
        cout<<"type: "<<type<<endl;
        if(type==NODE_VAL){
          cout<<"value: "<<value<<endl;
        }
        if(first!=NULL){
          first->printnodes();
        }
        if(second!=NULL){
          second->printnodes();
        }
        if(third!=NULL){
          third->printnodes();
        }
      }

      int execute(){
        vector<double> argslis;
        if(GLOBALreturned) {return GLOBALretval;}
        switch(type){
          case NODE_RETURN: 
            GLOBALretval = first->execute();
            GLOBALreturned = true;
            // cout<<"returning here "<<first->execute()<<endl;
            break;
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
              exec_context.set(symbol, first->execute());
            return exec_context.get(symbol);
            break;
          case NODE_DECLARE:
            if(exec_context.count(symbol)==0)
              exec_context.set(symbol,0);
            break;
          case NODE_EXPR:
            return first->execute();
            break;
          case NODE_PRINT:
          if(symbol.empty())
            cout << first->execute() << endl;
          else {
            cout << symbol <<":"<< first->execute() << endl; 
          }
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
            return exec_context.get(symbol);
            break;
          case NODE_VAL:
            return value;
            break;
          case NODE_CALL:
            // if(first==NULL){
              // cout<<"tre.hpp 165"<<endl;
              GLOBALreturned = false;
              if(first!=NULL){
                for(auto x:first->list()){
                  argslis.push_back(x);
                }
              }
              // cout<<"tre.hpp 172"<<endl;
              exec_context.push();
              // cout<<"tre.hpp 175"<<endl;
              if(func_table.count(symbol)!=0){
                vector<string> varnames = func_table[symbol].args_list;
                if(varnames.size()==argslis.size()){
                  for(int i=0;i<varnames.size();i++){
                    exec_context.set(varnames[i],argslis[i]);
                  }
                }
                else{
                  cout << "Error: Function " << symbol << " takes " << varnames.size() << " arguments, but " << argslis.size() << " were given." << endl;
                }
                cout<<"calling "<<symbol<<"with arguments :"<<endl;
                for(auto x: argslis){
                  cout<<x<<" ";
                }
                cout<<"stacksize "<<exec_context.ec.size()<<endl;
                cout<<endl;
                ((treenode*) func_table[symbol].func_def_tree)->execute();
              }
              exec_context.pop();
              if(GLOBALreturned){
                GLOBALreturned = false;
                return GLOBALretval;
              }
              else
                return 0;
            // }
            break;
          case NODE_FUNC:
            // symbol, first is args, second is body
            func_table[symbol].func_def_tree = second;
            // cout<<"tre.hpp 192"<<endl;
            if(first!=NULL)
            func_table[symbol].args_list = first->plist();
            else func_table[symbol].args_list = vector<string> ();
            break;
          case NODE_ARGS:
            first->execute();
            if(second!=NULL){
              second->execute();
            }
            break;
        }
      }


    };
#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
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
#define NODE_IN 201902
#define NODE_FOR 3453245
#define NODE_BREAK 999999
#define NODE_CONTINUE 999988

using namespace std;

extern double GLOBALretval;
extern bool GLOBALreturned;
extern bool breakSet;
extern bool continueSet;
extern int enteredLoop;
extern int labelcount;
extern unordered_set<string> decl;
extern get_exec_context exec_context;
extern unordered_map<string,func_def> func_table;
class treenode{
  public:
      string getlabel(){
        labelcount++;
        return "label"+to_string(labelcount);
      }
      treenode *first,*second,*third,*fourth;
      int type;
      double value;
      string symbol;
      treenode(int code, treenode * _first=NULL, treenode* _second =NULL, treenode * _third=NULL, treenode* _fourth=NULL){
          type = code;
          first = _first;
          second = _second;
          third = _third;
          fourth = _fourth;
      }
      treenode(int code, string _symbol, treenode* _first = NULL,treenode* _second = NULL){
        type = code;
        symbol = _symbol;
        first = _first;
        second = _second;
        fourth = NULL;
      }
      treenode(int code, double val){
        type = code;
        value = val;
        first = NULL;
        second = NULL;
        third = NULL;
        fourth = NULL;
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
        // cout<<"\tplist"<<endl;
        sol.push_back(first->symbol);
        // cout<<"\tfirst->first->symbol"<<endl;
        if(second!=NULL){
          second->helperplist(sol);
        }
        return sol;
      }
      
      void printnodes(){
        cout<<"\ttype: "<<type<<endl;
        if(type==NODE_VAL){
          cout<<"\tvalue: "<<value<<endl;
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
        double inpstr;
        if(GLOBALreturned) {return GLOBALretval;}
        if(enteredLoop>0 && ( breakSet || continueSet )){
          return 0;
        }
        switch(type){
          case NODE_CONTINUE:
            continueSet = true;
            break;
          case NODE_BREAK:
            breakSet = true;
            break;
          case NODE_FOR:
          enteredLoop++;
            first->execute();
            while(second->execute()){
              fourth->execute();
              if(breakSet){
                breakSet = false;
                break;
              }
              continueSet = false;
              third->execute();
            }
          enteredLoop--;
            break;
          case NODE_RETURN: 
            GLOBALretval = first->execute();
            GLOBALreturned = true;
            // cout<<"\treturning here "<<first->execute()<<endl;
            break;
          case NODE_IN:
            cin>>inpstr;
            if(exec_context.count(symbol)!=0)
              exec_context.set(symbol, inpstr);
            return exec_context.get(symbol);
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
          enteredLoop++;
            while((int)first->execute()){
              second->execute();
              if(breakSet){
                breakSet = false;
                break;
              }
              continueSet = false;
            }
          enteredLoop--;
            break;
          case NODE_ASSIGN:
            if(second==NULL){
              if(exec_context.count(symbol)!=0)
                exec_context.set(symbol, first->execute());
              return exec_context.get(symbol);
            }
            else{
              int index = second->execute();
              if(exec_context.vcount(symbol)!=0)
                exec_context.set(symbol, first->execute(), index);
              return exec_context.get(symbol, index);
            }
            break;
          case NODE_DECLARE:
              if(first==NULL)
              exec_context.def(symbol,0);
              else
              exec_context.def(symbol,0,first->execute());
            break;
          case NODE_EXPR:
            return first->execute();
            break;
          case NODE_PRINT:
          // cout<<"\tprinting"<<endl;
          if(first!=NULL)
            cout << first->execute();
          else {
            if(symbol.size()!=2)
              cout << symbol.substr(1,symbol.length()-2); 
            else
              cout<<endl;
          }
            break;
          case NODE_OPER:
            if(first->symbol=="++"){
              if(exec_context.count(symbol)!=0)
                exec_context.set(symbol, exec_context.get(symbol)+1);
              return exec_context.get(symbol);
            }
            else if(first->symbol=="--"){
              if(exec_context.count(symbol)!=0)
                exec_context.set(symbol, exec_context.get(symbol)-1);
              return exec_context.get(symbol);
            }
            else if(second->symbol=="+"){
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
            else if (second->symbol=="%"){
              return first->execute() % third->execute();
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
          if(first==NULL)
            return exec_context.get(symbol);
          else
            return exec_context.get(symbol, first->execute());
            break;
          case NODE_VAL:
            return value;
            break;
          case NODE_CALL:
            // if(first==NULL){
              // cout<<"\ttre.hpp 165"<<endl;
              GLOBALreturned = false;
              if(first!=NULL){
                for(auto x:first->list()){
                  argslis.push_back(x);
                }
              }
              // cout<<"\ttre.hpp 172"<<endl;
              // cout<<"\tstack added"<<endl;
              exec_context.push();
              // cout<<"\ttre.hpp 175"<<endl;
              if(func_table.count(symbol)!=0){
                vector<string> varnames = func_table[symbol].args_list;
                
                if(varnames.size()==argslis.size()){
                  for(int i=0;i<varnames.size();i++){
                    // cout<<"\tadding arguments"<<endl;
                    exec_context.def(varnames[i],argslis[i]);
                  }
                }
                else{
                  cout << "Error: Function " << symbol << " takes " << varnames.size() << " arguments, but " << argslis.size() << " were given." << endl;
                }
                // cout<<"\tcalling "<<symbol<<"with arguments :"<<endl;
                // for(auto x: argslis){
                //   cout<<x<<" ";
                // }
                // cout<<"\tstacksize "<<exec_context.ec.size()<<endl;
                // cout<<endl;
                ((treenode*) func_table[symbol].func_def_tree)->execute();
              }
              exec_context.pop();
              if(GLOBALreturned){
                // cout<<"\tstack removed with value "<<GLOBALretval<<endl;
                GLOBALreturned = false;
                return GLOBALretval;
              }
              else{
                // cout<<"\tstack removed"<<endl;
                return 0;
              }
            // }
            break;
          case NODE_FUNC:
            // symbol, first is args, second is body
            func_table[symbol].func_def_tree = second;
            // cout<<"\ttre.hpp 192"<<endl;
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

      int compile(){
        vector<double> argslis;
        double inpstr;
        string templ,templ2;
        switch(type){
          case NODE_STATEMENTS:
            first->compile();
            if(second!=NULL)
              second->compile();
            break;
          case NODE_ASSIGN:
            first->compile();
            if(decl.count(symbol)==0){
              cout<<"using undeclared symbol"<<endl;
              exit(0);
            }
            cout<< "\tpop " << symbol << endl;
            break;
          case NODE_DECLARE:
              cout<<"\tdecl "<<symbol<<endl;
              decl.insert(symbol);
            break; 
          case NODE_EXPR:
            first->compile();
            break;
          case NODE_PRINT:
          // cout<<"\tprinting"<<endl;
          if(first!=NULL){
            first->compile();
            cout<<"\tprint"<<endl;
          }
          else {
            if(symbol.size()!=2)
              cout << "\tprint \"" <<symbol.substr(1,symbol.length()-2)<<"\""<<endl; 
            else
              cout<< "\tprint \\n"<<endl;
          }
            break;
          case NODE_OPER:
            first->compile();
            third->compile();
            if(second->symbol=="+"){
              cout<<"\tadd"<<endl;
            }
            else if (second->symbol=="-"){
              cout<<"\tsub"<<endl;
            }
            else if(second->symbol=="*"){
              cout<<"\tmul"<<endl;
            }
            else if (second->symbol=="/"){
              cout<<"\tdiv"<<endl;
            }
            else if (second->symbol=="%"){
              cout<<"\tmod"<<endl;
            }
            break;
          case NODE_COMP:
            first->compile();
            third->compile();
            if(second->symbol=="=="){
              cout<< "\teq"<<endl;
            }
            else if (second->symbol=="!="){
              cout<< "\tneq"<<endl;
            }
            else if(second->symbol=="<"){
              cout<< "\tlt"<<endl;
            }
            else if (second->symbol==">"){
              cout<< "\tgt"<<endl;
            }
            else if(second->symbol=="<="){
              cout<< "\tleq"<<endl;
            }
            else if (second->symbol==">="){
              cout<< "\tgeq"<<endl;
            }
            break;
          case NODE_ID:
            if(decl.count(symbol)==0){
              cout<<"using undeclared symbol"<<endl;
              exit(0);
            }
            cout<<"\tpush " << symbol << endl;
            break;
          case NODE_VAL:
            cout<< "\tpush " << value << endl;
            break;
          case NODE_IF:
            first->compile();
            cout<<"\tpush 0"<<endl;
            templ = getlabel();
            cout<<"\tjeq "<<templ<<endl;
            second->compile();
            cout<<templ<<":"<<endl;
            break;
          case NODE_IFELSE:
            first->compile();
            cout<<"\tpush 0"<<endl;
            templ2 = getlabel();
            templ = getlabel();
            cout<<"\tjeq "<<templ<<endl;
            second->compile();
            cout<<"\tjmp "<<templ2<<endl;
            cout<<templ<<":"<<endl;
            third->compile();
            cout<<templ2<<":"<<endl;
            // //!
            // if(condition) statement1  else label1 statement2 label2

            // //! compilation of above line
            // translation of condition
            // jump to label1 if condition false
            // translation of statement 1
            // jump to after label2
            // this is label1
            // translation of statement 2
            // this is label2

            break;
          case NODE_FOR:
            first->compile();
            templ = getlabel();
            templ2 = getlabel();
            cout<<templ<<":"<<endl;
            second->compile();
            cout<<"\tpush 0"<<endl;
            cout<<"\tjeq "<<templ2<<endl;
            fourth->compile();
            third->compile();
            cout<<"\tjmp "<<templ<<endl;
            cout<<templ2<<":"<<endl;
            break;
            // //! for
            // for(st1;st2;st3){
            //   stmts;
            // }
            // //! compilation of above
            // translation of st1
            // lable1
            // translation of st2
            // jump to label2 if false;
            // translation of stmts
            // translation of st3
            // jump to label 1
            // label2
        }
      }
    };
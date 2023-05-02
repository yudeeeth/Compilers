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
#define NODE_ARR 314254

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

      void gendecl(vector<string> &decl){
        if(type==NODE_DECLARE){
          decl.push_back(symbol);
        }
        if(first!=NULL) first->gendecl(decl);
        if(second!=NULL) second->gendecl(decl);
        if(third!=NULL) third->gendecl(decl);
        if(fourth!=NULL) fourth->gendecl(decl);
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
              GLOBALreturned = false;
              //! getting list of args passed when calling
              if(first!=NULL){
                for(auto x:first->list()){
                  argslis.push_back(x);
                }
              }
              // unordered_set<string> isArr;
              // for(auto x: first->plist()){
              //   if(exec_context.vcount(x)!=0){
              //     isArr.insert(x);
              //   }
              // }
              //! adding new scope
              exec_context.push();
              //! adding and initialising the arguments in this scope
              if(func_table.count(symbol)!=0){
                vector<string> varnames = func_table[symbol].args_list;
                if(varnames.size()==argslis.size()){
                  for(int i=0;i<varnames.size();i++){
                    exec_context.def(varnames[i],argslis[i]);
                  }
                }
                //! calling the function node from table
                ((treenode*) func_table[symbol].func_def_tree)->execute();
              }
              //! removing new scope
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

      void printins(string ins, string var = ""){
        if(var != ""){
          cout<<"\t"<<ins<<" "<<var<<endl;
        }
        else{
          cout<<"\t"<<ins<<endl;
        }
      }
      
      string getrandomsuffix(){
        string k(10,'_');
        for(int i=1;i<10;i++){
          k[i] = rand()%26 + 'a';
        }
        return k;
      }

      string addsuffix(string var, unordered_map<string,int> &s){
        if(s.count(var)==0){
          return var;
        }
        // else return var+suff;
        // ST special register to push/pop into stacks[ith position]
        printins("push","xFP");
        printins("push",to_string( s[var] ));
        printins("add");
        return "ST";
      }

      int compile(unordered_map<string,int> varset = {}){
        vector<string> argslis;
        double inpstr;
        string templ,templ2;
        unordered_map<string,int> current_set(varset.begin(),varset.end());
        unordered_map<string,int> child_set;
        int it = 0 ;
        switch(type){
          case NODE_STATEMENTS:
            first->compile(current_set);
            if(second!=NULL)
              second->compile(current_set);
            break;
          case NODE_ASSIGN:
            first->compile(current_set);
            if(decl.count(symbol)==0){
              cout<<"using undeclared symbol"<<endl;
              cout<<"looking for "<<symbol<<":\n found:"<<endl;
              for(auto x: decl){
                cout<<x<<endl;
              }
              exit(0);
            }
            if(second != NULL){
              second->compile(current_set);
              printins("arr");
            }
            // cout<<"bitch"<<endl;
            printins("pop",addsuffix(symbol,current_set));
            break;
          case NODE_DECLARE:
              if(first!=NULL){
                first->compile();
                printins("arr");
              }
              printins("decl",addsuffix(symbol,current_set));
              decl.insert(symbol);
            break; 
          case NODE_EXPR:
            first->compile(current_set);
            break;
          case NODE_PRINT:
          // cout<<"\tprinting"<<endl;
          if(first!=NULL){
            first->compile(current_set);
            cout<<"\tprint"<<endl;
          }
          else {
            if(symbol.size()!=2)
              cout << "\tprint " <<symbol<<endl; 
            else
              cout<< "\tprint \"\""<<endl;
          }
            break;
          case NODE_OPER:
            first->compile(current_set);
            third->compile(current_set);
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
          case NODE_RETURN: 
            first->compile(current_set);
            printins("ret");
            break;
          case NODE_COMP:
            first->compile(current_set);
            third->compile(current_set);
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
            if( current_set.size()==0 && decl.count(addsuffix(symbol,current_set))==0){
              cout<<"using undeclared symbol"<<endl;
              exit(0);
            }
            if(first!=NULL){
              first->compile(current_set);
              printins("arr");
            }
            printins("push",addsuffix(symbol,current_set));
            // cout<<"\tpush " << symbol << endl;
            break;
          case NODE_FUNC:
            templ = getlabel();
            // child_suffix = getrandomsuffix();
            printins("jmp",templ);
            // set frame i.e push and update
            // In simulator set new fp to current stack location.
            // printins("push","xTOP");
            // return address
            cout<<symbol<<":"<<endl;
            cout<<"function is called here"<<endl;
            it = 0;
              if(first!=NULL){
                cout<<"inside first!=NULL"<<endl;
                argslis = first->plist();
                it = -argslis.size();
                for(auto x: argslis){
                  child_set[x] = it; it++;
                  // printins("pop",addsuffix(x,child_suffix,child_set));
                }
                // it + 1 = return address
                // it + 2 = num of args
                printins("push",to_string(argslis.size()));
                it = 3;
                argslis.clear();
                second->gendecl(argslis);
                for(auto x: argslis){
                  child_set[x] = it; it++;
                  printins("push",0);
                }
                cout<<"after pushing 0s"<<endl;
              }
              cout<<"exit first!=NULL"<<endl;
              second->compile(child_set);
            cout<<"before function exit"<<endl;
            cout<<templ<<":"<<endl;
            break;
          case NODE_CALL:
              if(first!=NULL)
                first->compile(current_set);
              printins("call",symbol);
            break;
          case NODE_VAL:
            printins("push",addsuffix(to_string(value),current_set));
            break;
          case NODE_IF:
            first->compile(current_set);
            cout<<"\tpush 0"<<endl;
            templ = getlabel();
            cout<<"\tjeq "<<templ<<endl;
            second->compile(current_set);
            cout<<templ<<":"<<endl;
            break;
          case NODE_IFELSE:
            first->compile(current_set);
            cout<<"\tpush 0"<<endl;
            templ2 = getlabel();
            templ = getlabel();
            cout<<"\tjeq "<<templ<<endl;
            second->compile(current_set);
            cout<<"\tjmp "<<templ2<<endl;
            cout<<templ<<":"<<endl;
            third->compile(current_set);
            cout<<templ2<<":"<<endl;
            break;
          case NODE_FOR:
            first->compile(current_set);
            templ = getlabel();
            templ2 = getlabel();
            cout<<templ<<":"<<endl;
            second->compile(current_set);
            cout<<"\tpush 0"<<endl;
            cout<<"\tjeq "<<templ2<<endl;
            fourth->compile(current_set);
            third->compile(current_set);
            cout<<"\tjmp "<<templ<<endl;
            cout<<templ2<<":"<<endl;
            break;
          case NODE_ARGS:
            first->compile(current_set);
            if(second!=NULL){
              second->compile(current_set);
            }
            break;
          case NODE_ARR:
            first->compile();
            argslis = first->plist();
            it = 0;
            printins("push",to_string(argslis.size()));
            printins("arr");
            printins("decl",addsuffix(symbol,current_set));
            for(it=argslis.size()-1;it>=0;it--){
              printins("push",to_string(it));
              printins("arr");
              printins("pop",addsuffix(symbol,current_set));
            }
            decl.insert(symbol);
        }
      }
    };
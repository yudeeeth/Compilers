#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;

class get_exec_context{
  public:
  vector<unordered_map<string, double>> ec;
  get_exec_context(vector<unordered_map<string, double>> exec_context){
    ec = exec_context;
    ec.push_back(std::unordered_map<std::string,double>());
  }
  double get(string str){
    for(int i=ec.size()-1;i>=0;i--){
      if(ec[i].count(str)!=0){
        return ec[i][str];
      }
    }
    return 0;
  }
  void def(string str, double val){
    ec.back()[str] = val;
  }
  void set(string str, double val){
    for(int i=ec.size()-1;i>=0;i--){
      if(ec[i].count(str)!=0){
        ec[i][str] = val;
        return;
      }
    }
    ec.back()[str] = val;
  }
  double count(string str){
    for(int i=ec.size()-1;i>=0;i--){
      if(ec[i].count(str)!=0){
        return true;
      }
    }
    return false;
  }
  void push(){
    ec.push_back(std::unordered_map<std::string,double>());
  }
  void pop(){
    ec.pop_back();
  }
};

#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
using namespace std;

class get_exec_context{
  public:
  vector<unordered_map<string, double>> ec;
  vector<unordered_map<string,vector<double> > > vec;
  get_exec_context(vector<unordered_map<string, double>> exec_context){
    ec = exec_context;
    vec = vector<unordered_map<string,vector<double>>>();
    ec.push_back(std::unordered_map<std::string,double>());
    vec.push_back(std::unordered_map<std::string,vector<double>>());
  }
  double get(string str){
    for(int i=ec.size()-1;i>=0;i--){
      if(ec[i].count(str)!=0){
        return ec[i][str];
      }
    }
    return 0;
  }
  double get(string str,int index){
    for(int i=vec.size()-1;i>=0;i--){
      if(vec[i].count(str)!=0){
        return vec[i][str][index];
      }
    }
    return 0;
  }
  void def(string str, double val){
    ec.back()[str] = val;
  }
  void def(string str, double val, int sz){
    vec.back()[str] = vector<double>(sz);
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
  void set(string str, double val, int index){
    for(int i=vec.size()-1;i>=0;i--){
      if(vec[i].count(str)!=0){
        vec[i][str][index] = val;
        return;
      }
    }
    // ec.back()[str][index] = val;
  }
  double count(string str){
    for(int i=ec.size()-1;i>=0;i--){
      if(ec[i].count(str)!=0){
        return true;
      }
    }
    return false;
  }
  double vcount(string str){
    for(int i=vec.size()-1;i>=0;i--){
      if(vec[i].count(str)!=0){
        return true;
      }
    }
    return false;
  }
  void push(){
    ec.push_back(std::unordered_map<std::string,double>());
    vec.push_back(std::unordered_map<std::string,vector<double>>());
  }
  void pop(){
    ec.pop_back();
    vec.pop_back();
  }
};

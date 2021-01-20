#ifndef INCLUDE_DAY18_HPP_
#define INCLUDE_DAY18_HPP_

#include<fstream>
#include<vector>
#include<map>
#include<unordered_map>
#include<string>
#include<iostream>
#include<utility>
#include<cstdint>
#include<regex>
#include<iomanip>

struct day18{


	day18(const string&filename){
		fstream e(filename);
		string s;
		getline(e,s);

		while(s.length()&&!e.eof())
		{
			operations.push_back(s);
			getline(e,s);
		}
	}

	int64_t eval(const string &s,unsigned& at){
		vector<int64_t> stack;
		char operation=' ';
		while(at<s.size())
		{
			switch(s[at]){
				case '+':
				case '-':
				case '*':
				case '/':
					operation=s[at];
					break;
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					stack.push_back(s[at]-'0');
					break;
				case '(':
					at++;
					stack.push_back(eval(s,at));
					break;
				case ')':
					return stack.back();
				default:
					break;
			}

			if(stack.size()>1){
				switch(operation){
					case '+':
						stack[0]=stack[0]+stack[1];
						stack.pop_back();
						break;
					case '-':
						stack[0]=stack[0]-stack[1];
						stack.pop_back();
						break;
					case '*':
						stack[0]=stack[0]*stack[1];
						stack.pop_back();
						break;
					case '/':
						stack[0]=stack[0]/stack[1];
						stack.pop_back();
						break;
					default:
						throw runtime_error("Found invalid operation "+s+" at "+to_string(at));
				}
			}

			at++;
		}

		return stack.back();
	}

	void getResult1(){
		int64_t acum=0;
		for(auto& op:operations){
			unsigned at=0;
			acum+=eval(op,at);
		}
		cout<<acum<<endl;

	}

	int64_t reduce(const vector<int64_t> &stack){
		int64_t res=1;
		for(auto&v:stack)
			res*=v;

		return res;
	}

	int64_t eval2(const string &s,unsigned& at){
		vector<int64_t> stack;
		char operation=' ';
		bool time_to_reduce=false, operate=false;
		while(at<s.size()&&!time_to_reduce)
		{
			operate=false;
			switch(s[at]){
				case '+':
				case '*':
					operation=s[at];
					break;
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					stack.push_back(s[at]-'0');
					operate=true;
					break;
				case '(':
					at++;
					stack.push_back(eval2(s,at));
					operate=true;
					break;
				case ')':
					return reduce(stack);
				default:
 					break;
			}

			if(stack.size()>1&& operation=='+'&&operate){
				operation=' ';
				stack[stack.size()-2]=stack[stack.size()-2]+stack.back();
 				stack.pop_back();
			}

			at++;
		}

		return reduce(stack);
	}


	void getResult2(){
		int64_t acum=0;
		for(auto& op:operations){
			unsigned at=0;
			acum+=eval2(op,at);
		}
		cout<<acum<<endl;


	}

	vector<string> operations;
};



#endif

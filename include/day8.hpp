#ifndef INCLUDE_DAY8_HPP_
#define INCLUDE_DAY8_HPP_

#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<regex>
#include<utility>

using namespace std;

struct day8{

	struct instruction{
		enum OP {NOP,ACC,JMP};

		instruction(const string& s){
			regex r("([^ ]+) ([+-][0-9]+)");
			smatch match;
			regex_search(s,match,r);

			val=std::stol(match[2]);

			if(match[1]=="nop")
				operation=OP::NOP;
			else if(match[1]=="acc")
				operation=OP::ACC;
			else if(match[1]=="jmp")
				operation=OP::JMP;

		}

		OP operation;
		int val;
	};

	day8(const string&filename){

		fstream e(filename);
		string s;

		getline(e,s);

		while(s.length()){
			program.emplace_back(s);
			getline(e,s);

		}


	}

	pair<unsigned,int> run(){
		set<int> visited;
		unsigned current=0;
		int acum=0;
		while(current<program.size()){
			int inc=1;

			if(visited.count(current))
				break;

			switch(program[current].operation){
				case instruction::ACC:
					acum+=program[current].val;
					break;
				case instruction::JMP:
					inc=program[current].val;
					break;
				default:
					break;
			}

			visited.insert(current);
			current+=inc;
		}

		return pair<int,int>(current,acum);;
	}

	void getResult1(){
		cout<<"Acum value at repeated instruction: "<<run().second<<endl;
	}



	void getResult2(){
		for(auto& inst:program){
			switch(inst.operation){
				case instruction::ACC:
					break;
				case instruction::JMP:
				{
					inst.operation=instruction::NOP;
					auto r=run();
					if(r.first>=program.size())
					{
						cout<<"Valid instruction results in acum: "<<r.second<<endl;
						return;
					}
					inst.operation=instruction::JMP;
					break;
				}
				case instruction::NOP:
				{
					inst.operation=instruction::JMP;
					auto r=run();
					if(r.first>=program.size())
					{
						cout<<"Valid instruction results in acum: "<<r.second<<endl;
						return;
					}
					inst.operation=instruction::NOP;
					break;
				}
			}
		}

	}

	vector<instruction> program;
};



#endif /* INCLUDE_DAY8_HPP_ */

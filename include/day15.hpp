#ifndef INCLUDE_DAY15_HPP_
#define INCLUDE_DAY15_HPP_

#include<fstream>
#include<vector>
#include<map>
#include<unordered_map>
#include<string>
#include<iostream>
#include<utility>
#include<cstdint>
#include<regex>

using namespace std;

struct day15{

	day15(const string&filename){
		fstream  e(filename);
		uint64_t i;
		e>>i;
		while(!e.fail()){
			numbers.push_back(i);
			e.ignore();
			e>>i;
		}

	}

	void getResult1(){
		map<uint64_t,vector<uint64_t>> memory;
		uint64_t turn=1;
		uint64_t prev=0;

		for(auto& n:numbers){
			memory[n].push_back(turn);
			turn++;
			prev=n;
		}

		while(turn!=2021){
			if(memory[prev].size()>1){
				auto num=memory[prev].back()-memory[prev][memory[prev].size()-2];
				memory[num].push_back(turn);
				prev=num;
			}
			else{
				memory[0].push_back(turn);
				prev=0;
			}
			turn++;
		}

		cout<<"The 2020th number to be spoken is: "<<prev<<endl;


	}
	void getResult2(){
		unordered_map<uint64_t,vector<uint64_t>> memory;
		uint64_t turn=1;
		uint64_t prev=0;

		for(auto& n:numbers){
			memory[n].push_back(turn);
			turn++;
			prev=n;
		}

		while(turn!=30000001){
			if(memory[prev].size()>1){
				auto num=memory[prev].back()-memory[prev][memory[prev].size()-2];
				memory[num].push_back(turn);
				prev=num;
			}
			else{
				memory[0].push_back(turn);
				prev=0;
			}
			turn++;
		}

		cout<<"The 30000000th number to be spoken is: "<<prev<<endl;

	}

	vector<uint64_t> numbers;

};


#endif

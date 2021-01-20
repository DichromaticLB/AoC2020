#ifndef INCLUDE_DAY14_HPP_
#define INCLUDE_DAY14_HPP_

#include<fstream>
#include<vector>
#include<map>
#include<string>
#include<iostream>
#include<utility>
#include<cstdint>
#include<regex>

struct day14{

	struct bitmaskop{

		bitmaskop(const string& mk){
			clear=0;
			set=0;
			unsigned mx=mk.size();
			for(auto c:mk){
				mx--;
				clear<<=1;
				set<<=1;
				clear+=1;
				switch(c){
					case '1':
						set|=1;
						break;
					case '0':
						clear-=1;
						break;
					default:
						exs.push_back(mx);
						break;
				}
			}
		}

		uint64_t clear,set;
		vector<unsigned> exs;
		vector<pair<uint64_t,uint64_t>> asignations;

	};

	day14(const string& filename){
		fstream e(filename);
		string s;
		getline(e,s);

		regex bitmask("mask = ([X01]+)");
		regex memaddr("mem\\[([0-9]+)] = ([0-9]+)");
		smatch m;

		while(!e.eof()){

			regex_search(s,m,bitmask);
			operations.emplace_back(m[1]);
			getline(e,s);

			while(regex_match(s,memaddr)){
				regex_search(s,m,memaddr);
				operations.back().asignations.
						emplace_back(std::stoull(m[1]),std::stoull(m[2]));
				getline(e,s);
			}


		}
	}


	void getResult1(){
		map<uint64_t,uint64_t> memory;
		for(auto&op:operations){
			for(auto& memw:op.asignations)
				memory[memw.first]=(memw.second&op.clear)|op.set;
		}

		auto res=std::accumulate(memory.begin(),memory.end(),0L,[](const auto&l,const auto& r){
			return l + r.second;
		});

		cout<<"Values left in memory: "<<res<<endl;

	}

	void decode(uint64_t a){
		for(uint64_t i=63;i<64;i--)
		{
			cout<<(1&(a>>i));

		}
		cout<<endl;
	}



	uint64_t inject(uint64_t number,uint64_t iteration,
			const vector<unsigned>& vector){

		for(auto e=vector.rbegin();e!=vector.rend();e++){
			number&=~(1L<<*e);
			number|=(iteration&1)<<*e;
			iteration>>=1;
		}

		return number;
	}

	void getResult2(){
		map<uint64_t,uint64_t> memory;
		for(auto&op:operations)
			for(auto& memw:op.asignations){
				auto dir=memw.first;
				dir|=op.set;
				auto lim=(1UL<<op.exs.size());
				for(uint64_t i=0;i<lim;i++){
					memory[inject(dir,i,op.exs)]=memw.second;
				}


			}

		auto res=std::accumulate(memory.begin(),memory.end(),0L,[](const auto&l,const auto& r){
			return l + r.second;

		});


		cout<<"Values left in memory 2: "<<res<<endl;

	}

	vector<bitmaskop> operations;

};


#endif

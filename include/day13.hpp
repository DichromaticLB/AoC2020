#ifndef INCLUDE_DAY13_HPP_
#define INCLUDE_DAY13_HPP_

#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<utility>
#include<cstdint>
#include"util.hpp"

struct day13{

	using apair=pair<uint64_t,uint64_t>;

	day13(const string& s){
		fstream e(s);
		string ss;
		getline(e,ss);
		timestamp=stoul(ss);

		while(!e.eof()&&!e.fail()){
			if(e.peek()=='x'){
				busses.push_back(0);
				e.ignore(2);
			}else
			{
				busses.emplace_back();
				e>>busses.back();
				e.ignore();
				if(e.fail())
					busses.pop_back();
			}
		}

	}


	void getResult1(){
		unsigned minWait=numeric_limits<unsigned>::max();
		unsigned id=0;
		for(auto v:busses)
			if(v!=0){
				unsigned wtime=v*(timestamp/v+1);
				if(wtime-timestamp<minWait)
				{
					minWait=wtime-timestamp;
					id=v;
				}
			}
		cout<<"Result from busId X wait time: "<<minWait*id<<endl;
	}


	uint64_t _inverse(uint64_t num,uint64_t mod){
		for(uint64_t i=1;i<numeric_limits<uint64_t>::max();i++){
			if((num*i)%mod==1)
				return i;
		}
		return 0;
	}

	void getResult2(){
		vector<uint64_t> numbers;
		vector<uint64_t> remainders;
		vector<uint64_t> inverses;
		uint64_t distance=0,M=1,acum=0;

		for(auto v=busses.rbegin();v!=busses.rend();v++){
			if(*v){
				numbers.push_back(*v);
				remainders.push_back(distance);
				M*=*v;
			}
			distance++;
		}

		for(auto&v:numbers){
			inverses.push_back(_inverse(M/v,v));
		}

		for(unsigned e=0;e<numbers.size();e++){
			acum+=remainders[e]*inverses[e]*(M/numbers[e]);
		}

		acum%=M;
		cout<<acum-remainders.back()<<endl;

	}

	unsigned timestamp;
	vector<uint64_t> busses;
};


#endif

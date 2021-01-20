#ifndef INCLUDE_DAY25_HPP_
#define INCLUDE_DAY25_HPP_


#include<fstream>
#include<vector>
#include<map>
#include<list>
#include<unordered_map>
#include<string>
#include<iostream>
#include<utility>

using namespace std;


struct day25{

	day25(const string&s){
		card=door=0;
		fstream e(s);
		e>>card;
		e>>door;
	}

	uint64_t seek(uint64_t tgt){
		uint64_t num=1;
		for(uint64_t i=1;i<numeric_limits<uint64_t>::max();i++){

			num=(num*7)%20201227;

			if(num==tgt)
				return i;
		}

		return 0;
	}

	void getResult1(){
		uint64_t cpk,dpk;
		cpk=seek(card),dpk=seek(door);

		uint64_t num=1;
		for(uint64_t i=0;i<cpk;i++)
			num=(num*door)%20201227;

		cout<<"Encryption key: "<<num<<endl;



	}

	void getResult2(){}

	uint64_t card,door;
};


#endif

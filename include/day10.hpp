#ifndef INCLUDE_DAY10_HPP_
#define INCLUDE_DAY10_HPP_

#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>

using namespace std;

struct day10{


	day10(const string&filename){
		fstream e(filename);
		unsigned adapter;
		e>>adapter;

		while(!e.fail()){
			adapters.push_back(adapter);
			e>>adapter;
		}


	}

	void getResult1(){
		vector<unsigned> cp(1,0);
		unsigned oneDiff=0,threeDiff=1;

		cp.insert(cp.end(),adapters.begin(),adapters.end());
		sort(cp.begin(),cp.end());

		for(unsigned i=1;i<cp.size();i++)
		{
			switch(cp[i]-cp[i-1]){
			case 1:
				oneDiff++;
				break;
			case 3:
				threeDiff++;
				break;
			default:
				break;

			}
		}

		cout<<"1 differences X 3 differences = "<<oneDiff*threeDiff<<endl;

	}



	void getResult2(){
		sort(adapters.begin(),adapters.end());
		map<unsigned,unsigned long long> cache={{adapters.back()+3,1}};

		for(auto e=adapters.rbegin();e!=adapters.rend();e++){
			unsigned long long acum=0;
			for(auto& p:cache){
				if(p.first-*e<4){
					acum+=p.second;
				}
			}
			cache[*e]=acum;
		}
		cout<<"The number of possible paths is: "<<cache[1]+cache[2]+cache[3]<<endl;
		return;
	}

	vector<unsigned> adapters;
};

#endif

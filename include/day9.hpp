#ifndef INCLUDE_DAY9_HPP_
#define INCLUDE_DAY9_HPP_

#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<numeric>

using namespace std;

struct day9{


	day9(const string&filename){
		fstream e(filename);
		string s;
		getline(e,s);
		while(s.size())
		{
			values.push_back(std::stoull(s));
			getline(e,s);
		}

	}

	bool match(unsigned index){
		for(unsigned e=0;e<25;e++){

			auto target=values[index]-values[index-25+e];

			if(target==values[index-25+e])
				continue;

			auto result=find(values.data()+index-25,values.data()+index,target);
			if(result!=values.data()+index)
				return true;
		}

		return false;
	}

	void getResult1(){
		for(unsigned i=25;i<values.size();i++){
			if(!match(i))
			{
				cout<<"First number to not match: "<<values[i]<<endl;
				return;
			}

		}

	}

	void getResult2(){
		unsigned target=0;

		for(unsigned i=25;i<values.size();i++)
		{
			if(!match(i)){
				target=values[i];
				break;
			}
		}

		auto left=values.data(),right=values.data();


		while(true){
			unsigned current=accumulate(left,right,0);

			if(current==target)
			{
				sort(left,right);
				cout<<"Found pair of numbers "<<(*left)<<"+"<<*(right-1)<<" = "<<(*left)+*(right-1)<<endl;
				return;
			}
			else if(current>target)
				left++;
			else
				right++;

		}


	}

	vector<unsigned long long> values;
};

#endif

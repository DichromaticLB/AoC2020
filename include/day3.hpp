#ifndef INCLUDE_DAY3_HPP_
#define INCLUDE_DAY3_HPP_

#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<utility>

using namespace std;

struct day3{

	day3(const string & filename){
		fstream e(filename);
		string s;
		getline(e,s);

		while(!e.fail()){
			lines.push_back(s);
			getline(e,s);
		}
	}

	int travel(int x,int y){
		int w=lines[0].length();
		int index=0;
		int count=0;

		for(unsigned i=0;i<lines.size();i+=y)
		{
			if(lines[i][index%w]=='#')
				count++;
			index+=x;
		}

		return count;
	}

	void getResult1(){
		cout<<"Found a total of "<<travel(3,1)<<" trees"<<endl;
	}

	void getResult2(){
		vector<pair<int,int>> slopes={{1,1},{3,1},{5,1},{7,1},{1,2}};
		int result=1;
		for(auto p:slopes)
			result*=travel(p.first,p.second);

		cout<<"Mult of all trees found on all tree slopes "<<result<<endl;
	}

	vector<string> lines;
};



#endif /* INCLUDE_DAY3_HPP_ */

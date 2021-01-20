#ifndef INCLUDE_DAY6_HPP_
#define INCLUDE_DAY6_HPP_

#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<utility>
#include<set>

struct day6{

	struct group{

		group(fstream&e){
			string s;
			getline(e,s);

			while(s.size()&&!e.eof())
			{
				answers.push_back(s);
				getline(e,s);
			}
		}

		int unique() const {
			set<char> res;
			for(auto& l:answers)
				for(auto& c:l)
					res.insert(c);
			return res.size();
		}

		int unique2() const {
			set<char> res(answers[0].begin(),answers[0].end());
			for(auto& s:answers){
				vector<char> swp(res.size());
				set<char> current(s.begin(),s.end());
				auto ret=set_intersection(res.begin(),res.end(),current.begin(),
						current.end(),swp.begin());
				res=set<char>(swp.begin(),ret);

			}
			return res.size();
		}

		vector<string> answers;
	};

	day6(const string&filename){
		fstream e(filename);

		while(!e.eof()){
			groups.emplace_back(e);
		}
	}

	void getResult1(){
		int res=0;
		for(auto&g:groups)
			res+=g.unique();
		cout<<"Sum of all unique answers per group: "<<res<<endl;

	}

	void getResult2(){
		int res=0;
		for(auto&g:groups)
			res+=g.unique2();
		cout<<"Sum of all intersetction answers per group: "<<res<<endl;
	}

	vector<group> groups;
};

#endif

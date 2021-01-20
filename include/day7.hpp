#ifndef INCLUDE_DAY7_HPP_
#define INCLUDE_DAY7_HPP_

#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<map>
#include<set>
#include<utility>
#include<regex>

using namespace std;

struct day7{

	struct rule{

		bool can_hold(const string&s) const{
			return can_contain.count(s)>0;
		}

		string bag_name;
		map<string,int> can_contain;
	};

	day7(const string& filename){
		fstream e(filename);
		string line;
		regex head("([^ ]+ [^ ]+) bags contain");
		regex tails("([0-9]) ([^ ]+ [^ ]+) bag");

		getline(e,line);

		while(line.size()){
			smatch m;

			rules.emplace_back();
			regex_search(line,m,head);
			rules.back().bag_name=m[1];
			line = m.suffix().str();

			while(regex_search(line,m,tails)){
				rules.back().can_contain.emplace(m[2],stoul(m[1]));
				line = m.suffix().str();
			}

			getline(e,line);
		}

	}

	void getResult1() const{
		set<string> to_visit={"shiny gold"};
		set<string> visited;

		while(to_visit.size()>0){
			string current=*to_visit.begin();
			visited.insert(current);
			to_visit.erase(current);

			for(auto& r:rules){
				if(r.can_hold(current)&&visited.count(r.bag_name)==0)
					to_visit.insert(r.bag_name);
			}
		}

		cout<<"A total of "<<visited.size()-1<<" can hold shiny gold bags"<<endl;

	}

	void getResult2() const{
		vector<string> toVisit={"shiny gold"};
		map<string,rule> mp;
		for(auto& r:rules)
			mp[r.bag_name]=r;

		int count=0;
		while(toVisit.size()){
			auto current=toVisit.back();
			toVisit.pop_back();

			if(mp.count(current)){
				for(auto& p:mp.at(current).can_contain)
				{
					count+=p.second;
					toVisit.insert(toVisit.end(),p.second,p.first);
				}
			}

		}

		cout<<"Your shiny gold bar must hold a total of: "<<count<<" bags"<<endl;

	}

	vector<rule> rules;

};



#endif

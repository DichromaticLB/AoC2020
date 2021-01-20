#ifndef INCLUDE_DAY4_HPP_
#define INCLUDE_DAY4_HPP_

#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<utility>
#include<map>
#include<regex>
#include<numeric>
#include<algorithm>

using namespace std;

struct day4{

	struct passport:map<string,string>{
		passport(fstream& e){

			string s;
			const regex entries("([^: ]+):([^: ]+)");
			getline(e,s);

			while(s.size()){
				smatch matches;

				while(regex_search(s,matches,entries)){
					(*this)[matches[1]]=matches[2];
					s = matches.suffix().str();
				}

				getline(e,s);
			}
		}

		bool valid1() const{
			vector<string> required={"byr","iyr","eyr","hgt","hcl","ecl","pid"};

			for(auto &s:required)
				if(!count(s))
					return false;

			return true;
		}

		bool valid2() const{
			if(!valid1())
				return false;

			unsigned num;

			num=stoul(at("byr"));

			if(num<1920||num>2002)
				return false;

			num=stoul(at("iyr"));

			if(num<2010||num>2020)
				return false;

			num=stoul(at("eyr"));

			if(num<2020||num>2030)
				return false;

			num=stoul(at("hgt"));

			string height_units(at("hgt").rbegin(),at("hgt").rbegin()+2);at("hgt");

			if(!((height_units=="mc"&&(num>=150&&num<=193))||(height_units=="ni"&&(num>=59&&num<=76))))
				return false;

			if(!regex_match(at("hcl"),regex("#[0-9a-f]{6}")))
				return false;

			vector<string> validecl={"amb","blu","brn","gry","grn","hzl","oth"};

			if(std::find(validecl.begin(),validecl.end(),at("ecl"))==validecl.end())
				return false;

			if(!regex_match(at("pid"),regex("[0-9]{9}")))
				return false;

			return true;

		}

	};

	day4(const string& filename){
		fstream e(filename);

		while(!e.eof()){
			passports.emplace_back(e);
		}
	}



	void getResult1(){
		auto res=accumulate(passports.begin(),passports.end(),0,
				[](int e,const passport& p1){return e+(p1.valid1()?1:0);});
		cout<<"valid passports: "<<res<<endl;
	}

	void getResult2(){
		auto res=accumulate(passports.begin(),passports.end(),0,
						[](int e,const passport& p1){return e+(p1.valid2()?1:0);});
				cout<<"valid passports 2nd criteria: "<<res<<endl;
	}

	vector<passport> passports;
};


#endif /* INCLUDE_DAY4_HPP_ */

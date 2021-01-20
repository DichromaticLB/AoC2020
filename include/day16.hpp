#ifndef INCLUDE_DAY16_HPP_
#define INCLUDE_DAY16_HPP_

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

	struct day16{

		using range=pair<uint64_t,uint64_t>;
		using ticket=vector<uint64_t>;

		struct field{
			string name;
			vector<range> valid;

			bool isValid(uint64_t t) const{
				bool res=false;
				for(auto&r:valid)
					if(t>=r.first&&t<=r.second)
						res=true;
				return res;
			}

		};

		day16(const string&filename){
			regex field("([a-z ]+): ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)");

			fstream e(filename);
			string s;
			smatch result;
			getline(e,s);


			while(regex_match(s,field)){
				regex_search(s,result,field);
				fields[result[1]].name=result[1];
				fields[result[1]].valid.emplace_back(stol(result[2]),stol(result[3]));
				fields[result[1]].valid.emplace_back(stol(result[4]),stol(result[5]));
				getline(e,s);
			}
			getline(e,s);

			do{
				myTicket.emplace_back();
				e>>myTicket.back();
			}while(e.get()==',');
			getline(e,s);
			getline(e,s);

			while(!e.eof()){
				tickets.emplace_back();
				do{
					tickets.back().emplace_back();
					e>>tickets.back().back();
				}while(e.get()==',');
			}
			tickets.pop_back();

		}


		void getResult1(){
			uint64_t tser=0;

			for(auto&t:tickets)
				for(auto&v:t)
				{
					bool good=false;
					for(auto &f:fields){
						if(f.second.isValid(v))
						{
							good=true;
							break;
						}
					}
					if(!good)
					{
						tser+=v;
						break;
					}
				}
			cout<<"tser: "<<tser<<endl;
		}

		void getResult2(){
			vector<ticket> validtTickets;
			for(auto&t:tickets)
			{
				validtTickets.push_back(t);
				for(auto&v:t)
				{
					bool good=false;
					for(auto &f:fields){
						if(f.second.isValid(v))
						{
							good=true;
							break;
						}
					}
					if(!good)
					{
						validtTickets.pop_back();
						break;
					}
				}
			}

			vector<set<string>> validPerField;

			for(unsigned i=0;i<myTicket.size();i++){
				validPerField.emplace_back();
				for(auto &f:fields){
					bool good=true;
					for(auto&t:validtTickets){
						if(!f.second.isValid(t[i]))
						{
							good=false;
							break;
						}
					}
					if(good)
						validPerField.back().insert(f.first);
				}
			}

			set<string> assigned;
			vector<string> match(myTicket.size());
			vector<string> output(myTicket.size());

			while(assigned.size()!=myTicket.size()){
				for(uint32_t i=0;i<myTicket.size();i++)
				{
					auto r=set_difference(validPerField[i].begin(),validPerField[i].end(),
							assigned.begin(),assigned.end(),output.begin());
					if(r-output.begin()==1){
						match[i]=output.front();
						assigned.insert(output.front());
						break;
					}
				}
			}
			uint64_t res=1;
			for(unsigned e=0;e<match.size();e++){
				if(match[e].find("departure")!=string::npos)
					res*=myTicket[e];
			}
			cout<<"Multiplication of the fields starting with departure: "<<res<<endl;

		}

		ticket myTicket;
		vector<ticket> tickets;
		map<string,field> fields;


	};


#endif

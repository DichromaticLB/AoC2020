#ifndef INCLUDE_DAY19_HPP_
#define INCLUDE_DAY19_HPP_

#include<fstream>
#include<vector>
#include<map>
#include<unordered_map>
#include<string>
#include<iostream>
#include<utility>
#include<cstdint>
#include<regex>
#include<list>

using namespace std;


struct expression;
struct sexpression;
using terminal=map<char,unsigned>;
using emap=map<unsigned,expression>;


struct sexpression{
	string express(map<unsigned,string>& m,string append=""){
		string res="(";

		for(unsigned e=0;e<elems.size();e++){
			res+=m[elems[e]]+append;
		}

		return res+")";
	}

	vector<unsigned> elems;

};

struct expression{
	expression (){}
	expression (fstream&e){
		validForms.emplace_back();
		while(true)
		{
			switch(e.peek()){
				case ' ':
				case ':':
					e.ignore();
					break;
				case '|':
					validForms.emplace_back();
					e.ignore();
					break;
				case '\n':
					e.ignore();
					return;
				case '"':
					e.ignore();
					final.push_back(e.get());
					e.ignore(2);
					return;
				default:
					validForms.back().elems.emplace_back();
					e>>validForms.back().elems.back();
					break;
			}
		}
	}

	bool canBeExpressed(map<unsigned,string>& m){
		for(auto& v:validForms)
			for(auto n:v.elems)
				if(!m.count(n))
					return false;

		return true;
	}

	string express(map<unsigned,string>& m,string append1="",string append2=""){
		string res="(";
		for(unsigned e=0;e<validForms.size();e++){
			if(e>0)
				res+="|";
			res+=validForms[e].express(m,append2)+append1;
		}

		res+=")";
		return res;
	}

	vector<sexpression> validForms;
	string final;
};


	ostream& operator<<(ostream& e,const expression& ex){
		for(unsigned i=0;i<ex.validForms.size();i++){
			if(i!=0)
				e<<" | ";
			for(auto& v:ex.validForms[i].elems)
				e<<v<<" ";
		}

		return e;
	}

struct day19{

	struct elist{

		unsigned& operator[](unsigned e){
			auto s=data.begin();
			while(e--)
				s++;
			return *s;
		}
		list<unsigned> data;
	};


	day19(const string& filename){
		fstream e(filename);
		string s;
		unsigned num;

		while(e.peek()!='\n'){
			e>>num;
			expression s(e);
			expressions[num]=s;

			if(s.final.length())
				termsymbols[s.final[0]]=num;
		}


		e.ignore();
		getline(e,s);
		while(s.length()){
			messages.push_back(s);
			getline(e,s);
		}

	}

	void getResult1(){
		map<unsigned,string> replacements;
		for(auto& t:termsymbols){
			replacements[t.second]+=t.first;
		}

		while(replacements.size()!=expressions.size()){
			for(auto& v:expressions)
				if(!replacements.count(v.first)
						&&v.second.canBeExpressed(replacements)){
					auto r=v.second.express(replacements);
					replacements[v.first]=r;
				}
		}

		regex r(replacements[0]);
		unsigned count=0;
		for(auto &m:messages){
			if(regex_match(m,r))
				count++;
		}

		cout<<"A total of "<<count<<" messages match rule 0"<<endl;


	}

	void getResult2(){
		map<unsigned,string> replacements;
		for(auto& t:termsymbols){
			replacements[t.second]+=t.first;
		}


		while(replacements.size()!=expressions.size()){
			for(auto& v:expressions)
				if(!replacements.count(v.first)
						&&v.second.canBeExpressed(replacements)){
					if(v.first==8)
					{
						auto r=v.second.express(replacements,"","+");

						replacements[v.first]=r;
					}
					else if(v.first==11)
					{
						//Yikes :D
						string acum="(";
						for(unsigned e=1;e<5;e++)
						{
							if(e!=1)
								acum+="|";
							auto r=v.second.express(replacements,"","{"+to_string(e)+"}");
							acum+=r;
						}
						acum+=")";
						replacements[v.first]=acum;
					}
					else
					{
						auto r=v.second.express(replacements);
						replacements[v.first]=r;
					}

				}
		}

		regex r(replacements[0]);
		unsigned count=0;
		for(auto &m:messages){
			if(regex_match(m,r))
				count++;
		}

		cout<<"A total of "<<count<<" messages match rule 0 in case 2"<<endl;

	}

	terminal termsymbols;
	emap expressions;
	vector<string> messages;

};




#endif

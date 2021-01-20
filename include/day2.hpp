#ifndef INCLUDE_DAY2_HPP_
#define INCLUDE_DAY2_HPP_

#include<fstream>
#include<vector>
#include<string>
#include<iostream>

using namespace std;

struct day2{

	struct password_pattern{

		password_pattern(fstream& e){
			e>>min;
			e.ignore();
			e>>max;
			e.ignore();
			e>>req;
			e.ignore(2);
			e>>password;

		};

		bool complies(){
			int count=0;

			for(auto&c :password)
				if(c==req)
					count++;

			return count>=min&&count<=max;
		}

		bool complies2(){
			return (password[min-1]==req)^(password[max-1]==req);
		}

		int min,max;
		char req;
		string password;
	};

	day2(const string & filename){
		fstream e(filename);

		while(!e.fail()){

			password_pattern p(e);
			if(!e.fail())
				patterns.push_back(p);
		}
	}

	void getResult1(){
		int count=0;

		for(auto& p:patterns)
			if(p.complies())
				count++;

		cout<<"A total of "<<count<<" passwords comply"<<endl;
	}

	void getResult2(){
		int count=0;

		for(auto& p:patterns)
			if(p.complies2())
				count++;

		cout<<"A total of "<<count<<" passwords comply the 2nd policy"<<endl;
	}

	vector<password_pattern> patterns;


};



#endif

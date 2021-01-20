#ifndef INCLUDE_DAY22_HPP_
#define INCLUDE_DAY22_HPP_

#include<fstream>
#include<vector>
#include<map>
#include<list>
#include<unordered_map>
#include<string>
#include<iostream>
#include<utility>

struct day22{

	day22(const string& filename){
		fstream e(filename);

		e.ignore(100,'\n');
		while(e.peek()!='\n'){
			p1.emplace_back();
			e>>p1.back();
			e.ignore();
		}

		e.ignore();

		e.ignore(100,'\n');
		while(e.peek()!=EOF){
			p2.emplace_back();
			e>>p2.back();
			e.ignore();
		}
	}

	void getResult1(){
		list<unsigned> p1=this->p1,p2=this->p2;

		while(p1.size()>0&&p2.size()>0){
			unsigned c1=p1.front(),c2=p2.front();
			p1.pop_front();
			p2.pop_front();
			if(c1>c2)
			{
				p1.push_back(c1);
				p1.push_back(c2);
			}
			else
			{
				p2.push_back(c2);
				p2.push_back(c1);
			}
		}

		if(p2.size())
			p1=p2;

		unsigned res=0;
		while(p1.size())
		{
			res+=p1.front()*p1.size();
			p1.pop_front();
		}

		cout<<"Winner score: "<<res<<endl;

	}

	unsigned recurseGame(list<unsigned> p1,list<unsigned> p2,int level=0){
		using ilist=list<unsigned>;
		using config=pair<ilist,ilist>;

		set<config> prevs;
		while(p1.size()>0&&p2.size()>0){
			auto cc=config(p1,p2);

			if(prevs.count(cc))
			{
				if(level==0)
				{
					unsigned res=0;
					while(p1.size())
					{
						res+=p1.front()*p1.size();
						p1.pop_front();
					}
					cout<<"Winner score: "<<res<<endl;
				}

				return 1;
			}
			else
				prevs.insert(cc);


			unsigned c1=p1.front(),c2=p2.front();
			p1.pop_front(),p2.pop_front();
			unsigned res=0;
			if(p1.size()>=c1&&p2.size()>=c2){
				auto ip1=p1.begin(),ip2=p2.begin();
				advance(ip1,c1);
				advance(ip2,c2);
				res=recurseGame(ilist(p1.begin(),ip1),ilist(p2.begin(),ip2),level+1);
			}
			else
			{
				if(c1>c2)
					res=1;
				else
					res=2;
			}

			if(res==1){
				p1.push_back(c1);
				p1.push_back(c2);
			}
			else
			{
				p2.push_back(c2);
				p2.push_back(c1);
			}
		}
		unsigned winner=1;

		if(p2.size()){
			winner=2;
			p1=p2;
		}

		if(level==0)
		{
			unsigned res=0;
			while(p1.size())
			{
				res+=p1.front()*p1.size();
				p1.pop_front();
			}
			cout<<"Winner score: "<<res<<endl;
		}

		return winner;
	}

	void getResult2(){

		recurseGame(p1,p2);
	}

	list<unsigned> p1,p2;
};

#endif

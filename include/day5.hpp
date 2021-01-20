#ifndef INCLUDE_DAY5_HPP_
#define INCLUDE_DAY5_HPP_

#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<utility>

struct day5{


	day5(const string& s){
		fstream e(s);

		while(!e.fail()){
			seats.emplace_back();
			e>>seats.back();
		}
		seats.pop_back();

	}

	pair<int,int> decode(const string&s) const{
		int f=0,b=128,l=0,r=8;
		for(auto c:s){
			switch(c){
			case 'F':
				b-=(b-f)/2;
				break;
			case 'B':
				f+=(b-f)/2;
				break;
			case 'L':
				r-=(r-l)/2;
				break;
			case 'R':
				l+=(r-l)/2;
				break;
			}
		}
		return pair<int,int>(f,l);
	}

	void getResult1(){
		int highest=0;
		for(auto& s:seats){
			auto res=decode(s);
			if(res.first*8+res.second>highest)
				highest=res.first*8+res.second;
		}
		cout<<"sanity check max value: "<<highest<<endl;
	}

	void getResult2(){
		vector<vector<bool>> seat_status(8);
		for(auto &s:seat_status)
			s.resize(128,false);

		for(auto& s:seats)
		{
			auto r=decode(s);
			seat_status[r.second][r.first]=true;
		}

		for(int col=1;col<127;col++)
			for(int row =0;row<8;row++)
				if(!seat_status[row][col]&&seat_status[row][col-1]&&seat_status[row][col+1])
				{
					cout<<"your seat is at row: "<<row<<" col "<<col<<" id: "<<(col*8+row)<<endl;
					return;
				}
	}

	vector<string> seats;
};

#endif

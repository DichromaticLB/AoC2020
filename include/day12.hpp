#ifndef INCLUDE_DAY12_HPP_
#define INCLUDE_DAY12_HPP_

#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<utility>
using namespace std;

struct day12{

	using command=pair<char,int>;

	struct boat{

		boat(){
			NS=WE=0;
			orientation=0;
		}

		void takeOrder(command&c){
			switch(c.first){
				case 'N':
					NS+=c.second;
					break;
				case 'S':
					NS-=c.second;
					break;
				case 'W':
					WE-=c.second;
					break;
				case 'E':
					WE+=c.second;
					break;
				case 'F':
					switch(orientation){
						case 0:
							WE+=c.second;
							break;
						case 1:
							NS-=c.second;
							break;
						case 2:
							WE-=c.second;
							break;
						case 3:
							NS+=c.second;
							break;
					}
					break;
					case 'R':
						turn(c.second);
						break;
					case 'L':
						turn(360-c.second);
						break;
			}
		}

		void turn(int e){
			orientation=(orientation+e/90)%4;
		}

		char orientation;
		int NS,WE;
	};

	struct boat2{

		boat2(){
			NS=WE=0;
			WNS=1;
			WWE=10;
		}

		void takeOrder(command& c){
			switch(c.first){
				case 'N':
					WNS+=c.second;
					break;
				case 'S':
					WNS-=c.second;
					break;
				case 'W':
					WWE-=c.second;
					break;
				case 'E':
					WWE+=c.second;
					break;
				case 'F':
					NS+=c.second*WNS;
					WE+=c.second*WWE;
					break;
				case 'R':
					turn(c.second);
					break;
				case 'L':
					turn(360-c.second);
					break;
			}
		}

		void turn(int e){
			int _WNS=WNS;
			switch(e){
			case 90:
				WNS=-WWE;
				WWE=_WNS;
				break;
			case 180:
				WNS*=-1;
				WWE*=-1;
				break;
			case 270:
				WNS=WWE;
				WWE=-_WNS;
				break;
			}

		}

		int NS,WE,WNS,WWE;
	};


	day12(const string&filename){
		fstream e(filename);
		string s;
		getline(e,s);

		while(s.length()){
			commands.emplace_back(s[0],std::stoi(s.substr(1)));
			getline(e,s);
		}

	}

	void getResult1(){
		boat b;

		for(auto c:commands)
			b.takeOrder(c);
		cout<<"Manhattan distance:" <<abs(b.NS)+abs(b.WE)<<endl;

	}
	void getResult2(){
		boat2 b;

		for(auto c:commands)
			b.takeOrder(c);
		cout<<"Manhattan distance:" <<abs(b.NS)+abs(b.WE)<<endl;

	}

	vector<command> commands;
};



#endif

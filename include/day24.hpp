#ifndef INCLUDE_DAY24_HPP_
#define INCLUDE_DAY24_HPP_

#include<fstream>
#include<vector>
#include<map>
#include<list>
#include<unordered_map>
#include<string>
#include<iostream>
#include<utility>

using namespace std;

struct day24{

	struct path{
		enum step{ e, se, sw, w, nw, ne};

		path(fstream&e){

			while(e.peek()!='\n')
				switch(e.get()){
					case 'e':
						steps.push_back(step::e);
						break;
					case 'w':
						steps.push_back(step::w);
						break;
					case 's':
					{
						if(e.get()=='e')
							steps.push_back(step::se);
						else
							steps.push_back(step::sw);
						break;
					}
					case 'n':
					{
						if(e.get()=='e')
							steps.push_back(step::ne);
						else
							steps.push_back(step::nw);
						break;
					}
				}
			e.get();
		}

		pair<int,int> end(){
			int x=0,y=0;

			for(auto&s:steps){
				switch(s){
					case step::e:
						x+=2;
						break;
					case step::w:
						x-=2;
						break;
					case step::sw:
						x-=1;
						y-=1;
						break;
					case step::se:
						x+=1;
						y-=1;
						break;
					case step::nw:
						x-=1;
						y+=1;
						break;
					case step::ne:
						x+=1;
						y+=1;
						break;
				}
			}

			return pair<int,int>(x,y);
		}

		vector<step> steps;
	};

	day24(const string & filename){
		fstream e(filename);

		while(e.peek()!=EOF)
			paths.emplace_back(e);

	}

	void getResult1(){
		map<pair<int,int>,bool> board;

		for(auto& p:paths){
			auto res=p.end();
			board[res]^=true;
		}

		auto blackTiles=accumulate(board.begin(),board.end(),0,[](unsigned e,const auto& v){
			return e+((v.second)?1:0);
		});

		cout<<"Total black tiles: "<<blackTiles<<endl;
	}

	vector<pair<int,int>> tilesAround(int x,int y){

		vector<pair<int,int>> res={{2,0},{-2,0},{1,1},{-1,1},{1,-1},{-1,-1}};

		for(auto&v:res)
		{
			v.first+=x;
			v.second+=y;
		}

		return res;
	}

	void getResult2(){
		map<pair<int,int>,bool> board;

		for(auto& p:paths){
			auto res=p.end();
			board[res]^=true;
		}

		for(unsigned i=0;i<100;i++){
			map<pair<int,int>,unsigned> blackNeighbours;
			for(auto& v:board){
				if(v.second)
				{
					auto tar=tilesAround(v.first.first,v.first.second);
					for(auto&n:tar)
						blackNeighbours[n]++;
				}
			}

			map<pair<int,int>,bool> buffer;

			for(auto&v:board){
				if(v.second)
				{
					auto ct=blackNeighbours[v.first];
					if(ct==1||ct==2)
						buffer[v.first]=true;
				}
			}

			for(auto&v:blackNeighbours){
				if(v.second==2&&!board[v.first])
					buffer[v.first]=true;
			}

			board=buffer;
		}

		auto blackTiles=accumulate(board.begin(),board.end(),0,[](unsigned e,const auto& v){
			return e+((v.second)?1:0);
		});

		cout<<"Total black tiles after 100 days: "<<blackTiles<<endl;
	}

	vector<path> paths;
};


#endif

#ifndef INCLUDE_DAY17_HPP_
#define INCLUDE_DAY17_HPP_

#include<fstream>
#include<vector>
#include<map>
#include<unordered_map>
#include<string>
#include<iostream>
#include<utility>
#include<cstdint>
#include<regex>
#include<iomanip>

using namespace std;

struct day17{

	struct coordinate{
		int x,y,z,w;

		coordinate getNeighbour3(uint8_t num) const{
			const static coordinate neighbourPos[]={
					{-1, -1, -1, 0},
					{-1, -1,  0, 0},
					{-1, -1,  1, 0},
					{-1,  0, -1, 0},
					{-1,  0,  0, 0},
					{-1,  0,  1, 0},
					{-1,  1, -1, 0},
					{-1,  1,  0, 0},
					{-1,  1,  1, 0},
					{ 0, -1, -1, 0},
					{ 0, -1,  0, 0},
					{ 0, -1,  1, 0},
					{ 0,  0, -1, 0},
					{ 0,  0,  1, 0},
					{ 0,  1, -1, 0},
					{ 0,  1,  0, 0},
					{ 0,  1,  1, 0},
					{ 1, -1, -1, 0},
					{ 1, -1,  0, 0},
					{ 1, -1,  1, 0},
					{ 1,  0, -1, 0},
					{ 1,  0,  0, 0},
					{ 1,  0,  1, 0},
					{ 1,  1, -1, 0},
					{ 1,  1,  0, 0},
					{ 1,  1,  1, 0}
			};

			return {x+neighbourPos[num].x,y+neighbourPos[num].y,z+neighbourPos[num].z,w+neighbourPos[num].w};
		}

		coordinate getNeighbour4(uint8_t num) const{
			const static coordinate neighbourPos[]={
					{-1,-1,-1,-1},
					{-1,-1,-1, 0},
					{-1,-1,-1, 1},
					{-1,-1, 0,-1},
					{-1,-1, 0, 0},
					{-1,-1, 0, 1},
					{-1,-1, 1,-1},
					{-1,-1, 1, 0},
					{-1,-1, 1, 1},
					{-1, 0,-1,-1},
					{-1, 0,-1, 0},
					{-1, 0,-1, 1},
					{-1, 0, 0,-1},
					{-1, 0, 0, 0},
					{-1, 0, 0, 1},
					{-1, 0, 1,-1},
					{-1, 0, 1, 0},
					{-1, 0, 1, 1},
					{-1, 1,-1,-1},
					{-1, 1,-1, 0},
					{-1, 1,-1, 1},
					{-1, 1, 0,-1},
					{-1, 1, 0, 0},
					{-1, 1, 0, 1},
					{-1, 1, 1,-1},
					{-1, 1, 1, 0},
					{-1, 1, 1, 1},
					{ 0,-1,-1,-1},
					{ 0,-1,-1, 0},
					{ 0,-1,-1, 1},
					{ 0,-1, 0,-1},
					{ 0,-1, 0, 0},
					{ 0,-1, 0, 1},
					{ 0,-1, 1,-1},
					{ 0,-1, 1, 0},
					{ 0,-1, 1, 1},
					{ 0, 0,-1,-1},
					{ 0, 0,-1, 0},
					{ 0, 0,-1, 1},
					{ 0, 0, 0,-1},
					{ 0, 0, 0, 1},
					{ 0, 0, 1,-1},
					{ 0, 0, 1, 0},
					{ 0, 0, 1, 1},
					{ 0, 1,-1,-1},
					{ 0, 1,-1, 0},
					{ 0, 1,-1, 1},
					{ 0, 1, 0,-1},
					{ 0, 1, 0, 0},
					{ 0, 1, 0, 1},
					{ 0, 1, 1,-1},
					{ 0, 1, 1, 0},
					{ 0, 1, 1, 1},
					{ 1,-1,-1,-1},
					{ 1,-1,-1, 0},
					{ 1,-1,-1, 1},
					{ 1,-1, 0,-1},
					{ 1,-1, 0, 0},
					{ 1,-1, 0, 1},
					{ 1,-1, 1,-1},
					{ 1,-1, 1, 0},
					{ 1,-1, 1, 1},
					{ 1, 0,-1,-1},
					{ 1, 0,-1, 0},
					{ 1, 0,-1, 1},
					{ 1, 0, 0,-1},
					{ 1, 0, 0, 0},
					{ 1, 0, 0, 1},
					{ 1, 0, 1,-1},
					{ 1, 0, 1, 0},
					{ 1, 0, 1, 1},
					{ 1, 1,-1,-1},
					{ 1, 1,-1, 0},
					{ 1, 1,-1, 1},
					{ 1, 1, 0,-1},
					{ 1, 1, 0, 0},
					{ 1, 1, 0, 1},
					{ 1, 1, 1,-1},
					{ 1, 1, 1, 0},
					{ 1, 1, 1, 1}
			};

			return {x+neighbourPos[num].x,y+neighbourPos[num].y,z+neighbourPos[num].z,w+neighbourPos[num].w};
		}


		bool operator< (const coordinate & other) const{
			if(x!=other.x)
				return x<other.x;
			if(y!=other.y)
				return y<other.y;
			if(z!=other.z)
				return z<other.z;
			return w<other.w;

		}
	};

	struct node{
		node(bool b,unsigned ac){active=b;active_neighbours=ac;}
		node(){active=false,active_neighbours=0;}
		bool active;
		unsigned active_neighbours;
	};
	using mworld=map<coordinate,node>;

	day17(const string& filename){

		fstream e(filename);
		int x=0,y=0;
		char c=e.get();
		while(!e.eof()){
			switch(c){
				case '.':
					world[{x++,y,0,0}]={false,0};
					break;
				case '#':
					world[{x++,y,0,0}]={true,0};
					break;
				default:
					x=0;
					y--;
					break;

			}
			c=e.get();
		}
	}

	void getResult1(){
		mworld copy,buffer;
		copy=buffer=world;

		for(unsigned e=0;e<6;e++){
			for(auto& i:copy){
				if(i.second.active)
					for(unsigned j=0;j<26;j++)
						buffer[i.first.getNeighbour3(j)].active_neighbours++;
            }

			for(auto&v:buffer){
				if(v.second.active)
				{
					if((v.second.active_neighbours!=2
							&&v.second.active_neighbours!=3))
						v.second.active=false;
				}
				else
				{
					if(v.second.active_neighbours==3)
						v.second.active=true;
				}

				v.second.active_neighbours=0;
			}

			copy=buffer;
		}

		unsigned res=0;
		for(auto&c:copy)
			if(c.second.active)
				res++;

		cout<<"Active cubes after 6th cycle: "<<res<<endl;
	}

	void getResult2(){
		mworld copy,buffer;
				copy=buffer=world;

				for(unsigned e=0;e<6;e++){
					for(auto& i:copy){
						if(i.second.active)
							for(unsigned j=0;j<80;j++)
								buffer[i.first.getNeighbour4(j)].active_neighbours++;
		            }

					for(auto&v:buffer){
						if(v.second.active)
						{
							if((v.second.active_neighbours!=2
									&&v.second.active_neighbours!=3))
								v.second.active=false;
						}
						else
						{
							if(v.second.active_neighbours==3)
								v.second.active=true;
						}

						v.second.active_neighbours=0;
					}

					copy=buffer;
				}

				unsigned res=0;
				for(auto&c:copy)
					if(c.second.active)
						res++;

				cout<<"Active cubes after 6th cycle in 4 dimensions : "<<res<<endl;

	}

	mworld world;
};


#endif

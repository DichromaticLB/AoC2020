#ifndef INCLUDE_DAY20_HPP_
#define INCLUDE_DAY20_HPP_

#include<fstream>
#include<vector>
#include<map>
#include<unordered_map>
#include<string>
#include<iostream>
#include<utility>
#include<cstdint>
#include"board.hpp"

using namespace std;

struct tilemap{
	tilemap():id(0){}
	tilemap(fstream& e):id(0){
		string s;
		e>>s;
		e>>id;
		e.ignore(2);
		vector<string> data;
		while(e.peek()!='\n'){
			data.emplace_back();
			getline(e,data.back());
		}
		tiles.resize(data.size(),data[0].size());

		for(auto e=tiles.begin();e!=tiles.end();++e){
			*e=data[e.row][e.col];
		}
	}

	vector<unsigned> fingerprints(){
		vector<unsigned> res(4);

		for(unsigned e=0;e<tiles.cols();e++){
			res[0]<<=1;
			res[0]|=(tiles.get(0,e)=='#')?1:0;
		}

		for(unsigned e=0;e<tiles.cols();e++){
			res[1]<<=1;
			res[1]|=(tiles.get(tiles.rows()-1,e)=='#')?1:0;
		}

		for(unsigned e=0;e<tiles.rows();e++){
			res[2]<<=1;
			res[2]|=(tiles.get(e,0)=='#')?1:0;
		}

		for(unsigned e=0;e<tiles.rows();e++){
			res[3]<<=1;
			res[3]|=(tiles.get(e,tiles.cols()-1)=='#')?1:0;
		}
		return res;
	}

	vector<unsigned> allFingerprints(){
		auto res=vector<unsigned>();
		for(unsigned i=0;i<4;i++){
			auto concat=fingerprints();
			res.insert(res.end(),concat.begin(),concat.end());
			tiles.rotateClockwise();
		}
		switcheroo();
		for(unsigned i=0;i<4;i++){
			auto concat=fingerprints();
			res.insert(res.end(),concat.begin(),concat.end());
			tiles.rotateClockwise();
		}
		switcheroo();

		return res;
	}

	void switcheroo(){
		tiles.vflip();
		tiles.hflip();
	}

	unsigned id;
	board<char,false> tiles;
};

ostream& operator<<(ostream& o,tilemap& t){

	o<<"Tile "<<t.id<<":"<<endl;
	unsigned e=0;
	for(auto& c:t.tiles){
		if(e>0&&!(e%t.tiles.cols()))
			o<<endl;
		o<<c;
		e++;
	}

	return o;
}

struct day20{

	day20(const string& filename){
		fstream e(filename);

		while(e.peek()!=EOF){
			entries.emplace_back(e);

			auto r=entries.back().fingerprints();
			e.ignore();
		}
	}

	void getResult1(){

		for(unsigned e=0;e<entries.size();e++){
			auto r=entries[e].fingerprints();

			set<unsigned> remaining(r.begin(),r.end());

			for(unsigned i=0;i<entries.size();i++)
			{
				if(i==e)
					continue;

				auto copy=entries[i];
				auto f1=copy.fingerprints();
				copy.switcheroo();
				auto f2=copy.fingerprints();
				copy.switcheroo();


				for(auto& v:f1)
					remaining.erase(v);
				for(auto& v:f2)
					remaining.erase(v);
			}

			if(remaining.size()==2)
				corners.push_back(e);
		}
		uint64_t res=1;

		for(auto& v:corners)
			res*=entries[v].id;

		cout<<"Corners mult: "<<res<<endl;
	}

	struct pos{
		int x;
		int y;
		pos left(){ return {x-1,y};}
		pos right(){ return {x+1,y};}
		pos top(){ return {x,y-1};}
		pos bot(){ return {x,y+1};}

		bool operator<(const pos& other) const{
			if(y==other.y)
				return x<other.x;
			return y<other.y;
		}
	};

	vector<pos> matches(tilemap& anchored,pos p,tilemap& free){
		vector<pos> res;
		auto af=anchored.fingerprints();
		auto ff=free.fingerprints();

		if(af[0]==ff[1])
			res.push_back(p.top());

		if(af[1]==ff[0])
			res.push_back(p.bot());

		if(af[2]==ff[3])
			res.push_back(p.left());

		if(af[3]==ff[2])
			res.push_back(p.right());

		return res;
	}

	vector<pos> checkSeaMonster(tilemap&m,int _x,int _y){
		static const vector<string> seamonster={
				"                  # ",
				"#    ##    ##    ###",
				" #  #  #  #  #  #   "
		};
		vector<pos> res;

		for(int y=0;y<seamonster.size();y++)
			for(int x=0;x<seamonster[y].size();x++)
			{
				if(seamonster[y][x]=='#')
				{
					if(m.tiles.get(_x+y,_y+x)!='#')
					{
						res.clear();
						return res;
					}
					else
					{
						res.push_back({_x+y,_y+x});
					}
				}
			}

		return res;
	}

	void getResult2(){
		map<unsigned,pos>  fit;
		map<unsigned,vector<unsigned>>  fitFingerprints;
		map<unsigned,set<unsigned>> fingerprints;

		for(unsigned e=0;e<entries.size();e++)
		{
			auto vec=entries[e].allFingerprints();
			fingerprints[e].insert(vec.begin(),vec.end());
		}

		fit[corners[0]]={0,0};
		fitFingerprints[corners[0]]=entries[corners[0]].fingerprints();

		while(fit.size()!=entries.size()){
			for(unsigned e=0;e<entries.size();e++){

				if(fit.count(e))
					continue;

				auto& af=fingerprints[e];

				for(auto&f:fit){
					bool valid=false;

					for(auto& v:fitFingerprints[f.first])
						if(af.count(v))
						{
							valid=true;
							break;
						}

					if(valid){
						bool done=false;

						for(unsigned j=0;j<4&&!done;j++)
						{
							auto m=matches(entries[f.first],f.second,entries[e]);
							if(m.size()){
								fit[e]=m[0];
								fitFingerprints[e]=entries[e].fingerprints();
								done=true;
								break;
							}
							entries[e].tiles.rotateClockwise();
						}

						if(!done)
							entries[e].tiles.vflip();
						for(unsigned j=0;j<4&&!done;j++)
						{
							auto m=matches(entries[f.first],f.second,entries[e]);
							if(m.size()){
								fit[e]=m[0];
								fitFingerprints[e]=entries[e].fingerprints();
								done=true;
								break;
							}
							entries[e].tiles.rotateClockwise();
						}

						if(!done)
							entries[e].tiles.hflip();
						for(unsigned j=0;j<4&&!done;j++)
						{
							auto m=matches(entries[f.first],f.second,entries[e]);
							if(m.size()){
								fit[e]=m[0];
								fitFingerprints[e]=entries[e].fingerprints();
								done=true;
								break;
							}
							entries[e].tiles.rotateClockwise();
						}
						break;
					}
				}
			}
		}
		map<pos,unsigned> recons;
		for(auto&f:fit)
			recons[f.second]=f.first;


		board<char,false> finalMap;
		int xstep=(entries[0].tiles.cols()-2),
			ystep=(entries[0].tiles.rows()-2),
			width=xstep*12,
			height=ystep*12;

		finalMap.resize(width,height);
		for(int y=0;y<height;y++)
			for(int x=0;x<width;x++){
				auto& src=recons[{(x/xstep),(y/ystep)}];

				finalMap.get(y,x)=
						entries[src].tiles.get(1+(y%ystep),1+(x%xstep));
			}


		tilemap m;
		finalMap.def='.';
		m.tiles=finalMap;


		m.tiles.hflip();
		set<pos> matching;
		for(int i=0;i<4;i++)
		{
			for(auto e=m.tiles.begin();e!=m.tiles.end();++e)
			{
				auto monster=checkSeaMonster(m,e.row,e.col);
				matching.insert(monster.begin(),monster.end());
			}

			if(matching.size()){
				unsigned count=0;
				for(auto e=m.tiles.begin();e!=m.tiles.end();++e){
					if(*e=='#'&&!matching.count(pos{(int)e.row,(int)e.col}))
						count++;
				}
				cout<<"rough water lvl: "<<count<<endl;
				return;
			}

			m.tiles.rotateClockwise();
		}
	}

	vector<tilemap> entries;
	vector<unsigned> corners;

};

#endif

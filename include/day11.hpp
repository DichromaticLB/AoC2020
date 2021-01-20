#ifndef INCLUDE_DAY11_HPP_
#define INCLUDE_DAY11_HPP_

#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include"board.hpp"

using namespace std;

struct seat{

	seat(){t=type::FREE;}
	enum type{
		FLOOR,
		FREE,
		OCCUPIED
	};

	bool operator!=(seat& o) const{
		return t!=o.t;
	}

	type t;
};

std::ostream& operator<<(ostream&o,seat& l){
	switch(l.t){
	case seat::FLOOR:
		o<<'.';
		break;
	case seat::FREE:
		o<<'L';
		break;
	case seat::OCCUPIED:
		o<<'#';
		break;
	}
	return o;
}
using board11=board<seat,false>;

struct day11{

	day11(const string& filename){
		vector<string> lines;
		fstream e(filename);
		string s;
		getline(e,s);

		while(s.size()){
			lines.push_back(s);
			getline(e,s);
		}

		elements.resize(lines.size(),lines[0].size());
		auto it=elements.begin();
		for(auto l:lines)
			for(auto c:l)
			{
				if(c=='.')
					(*it).t=seat::FLOOR;
				++it;
			}


	}


	void getResult1(){
		board11 copy=elements;
		while(true){
			board11 iter=copy;
			for(auto it=copy.begin();it!=copy.end();++it){
				switch((*it).t){
					case seat::FLOOR:
						break;
					case seat::FREE:
					{
						auto ar=it.around8();
						seat::type next=seat::OCCUPIED;

						for(auto s:ar)
							if(s.t==seat::OCCUPIED)
							{
								next=seat::FREE;
								break;
							}
						iter.get(it.row,it.col).t=next;

						break;
					}
					case seat::OCCUPIED:
					{
						auto ar=it.around8();
						unsigned around_occupied=accumulate(ar.begin(),ar.end(),0,[](unsigned e,seat& s){if(s.t==s.OCCUPIED)return e+1; return e;});
						if(around_occupied>3)
							iter.get(it.row,it.col).t=seat::FREE;

						break;
					}
				}
			}
			if(copy==iter){
				cout<<"Seats occupied after stabilization: "<<accumulate(copy.begin(),copy.end(),0,[](unsigned e,seat&s){
					if(s.t==s.OCCUPIED)
						return e+1;
					return e;
				})<<endl;
				return;
			}

			copy=iter;

		}


	}

	//Explore occupied seats
	unsigned eo(board11& b,unsigned r,unsigned c,int h,int v){
		while(true){
			r+=h,c+=v;
			switch(b.get(r,c).t){
				case seat::FLOOR:
					break;
				case seat::FREE:
					return 0;
				case seat::OCCUPIED:
					return 1;
			}
		}
	}

	void getResult2(){
		board11 copy=elements;
				while(true){
					board11 iter=copy;
					for(auto it=copy.begin();it!=copy.end();++it){
						switch((*it).t){
							case seat::FLOOR:
								break;
							case seat::FREE:
							case seat::OCCUPIED:
							{
								unsigned occ=eo(copy,it.row,it.col,-1,-1)+eo(copy,it.row,it.col,-1,0)+eo(copy,it.row,it.col,-1,+1)+
										eo(copy,it.row,it.col,0,-1)+eo(copy,it.row,it.col,0,+1)+eo(copy,it.row,it.col,+1,-1)+eo(copy,it.row,it.col,+1,0)+
										eo(copy,it.row,it.col,+1,1);
								if(occ==0&&(*it).t==seat::FREE)
									iter.get(it.row,it.col).t=seat::OCCUPIED;
								else if(occ>4)
									iter.get(it.row,it.col).t=seat::FREE;
								break;
							}

						}
					}
					if(copy==iter){
						cout<<"Seats occupied after stabilization 2: "<<accumulate(copy.begin(),copy.end(),0,[](unsigned e,seat&s){
							if(s.t==s.OCCUPIED)
								return e+1;
							return e;
						})<<endl;
						return;
					}

					copy=iter;

				}


			}

	board11 elements;

};




#endif /* INCLUDE_DAY11_HPP_ */

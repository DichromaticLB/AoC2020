#ifndef INCLUDE_BOARD_HPP_
#define INCLUDE_BOARD_HPP_

#include<vector>
#include<iostream>

template <class T,bool loop>
struct board{

	using row=std::vector<T>;

	void setDefault(const T&t){def=t;}

	void resize(int rows,int columns){
		elements.resize(rows);

		for(auto&e:elements)
			e.resize(columns);
	}

	T& get(unsigned row,unsigned col){
		if(loop)
			return elements[row%elements.size()][col%(elements[0].size())];
		else
		{
			if(row>=elements.size()||row<0||col>=elements[0].size()||col<0)
				return def;
			else
				return elements[row][col];
		}
	}

	unsigned rows() const{
		return elements.size();
	}

	unsigned cols() const{
		return elements[0].size();
	}

	bool operator!=(board<T,loop>& other){
		if(rows()!=other.rows()||cols()!=other.cols())
			return true;
		auto e=begin(),eo=other.begin();
		while(e!=end()){
			if((*e)!=(*eo))
				return true;
			++e;
			++eo;
		}
		return false;
	}

	void hflip(){
		auto copy=elements;
		for(auto e=begin();e!=end();++e){
			copy[e.row][cols()-(e.col+1)]=*e;
		}
		elements=copy;
	}

	void vflip(){
		auto copy=elements;
		for(auto e=begin();e!=end();++e){
			copy[rows()-(e.row+1)][e.col]=*e;
		}
		elements=copy;
	}

	void rotateClockwise(){
		vector<row> copy(cols());
		for(auto &r:copy)
			r.resize(rows());

		for(auto e=begin();e!=end();++e){
			copy[e.col][rows()-(e.row+1)]=*e;

		}
		elements=copy;
	}

	bool operator==(board<T,loop>& other){
		return !(operator !=(other));

	}


	struct iterator{

		T& operator*(){
			return self.get(row,col);
		}

		void operator++(){
			col++;
			if(col>=self.cols())
			{
				col=0;
				row++;
			}
		}

		bool operator!=(iterator t){
			return t.row!=row||t.col!=col;
		}

		//Returns top,right,bot,left
		//  1
		//4 X 2
		//  3
		vector<T> around4(){
			vector<T> res={self.get(row -1,col),self.get(row ,col+1),self.get(row +1,col),self.get(row ,col-1)};
			return res;
		}

		//Returns pieces around starting from the leftmost top and goes clockwise
		//1 2 3
		//8 X 4
		//7 6 5
		vector<T> around8(){
			vector<T> res={self.get(row-1,col-1),self.get(row-1,col),self.get(row-1,col+1),self.get(row,col+1),
					self.get(row+1,col+1),self.get(row+1,col),self.get(row+1,col-1),self.get(row,col-1)};
			return res;
		}


		board<T,loop>& self;
		long unsigned int row,col;
	};

	iterator begin(){
		return iterator {*this,0,0};
	}

	iterator end(){
		return iterator {*this,elements.size(),0};
	}


	T def;
	std::vector<row> elements;
};

template <class T,bool loop>
std::ostream& operator<<(ostream&o,board<T,loop>& l){
	auto nl=l.cols();
	unsigned at=0;
	for(auto el:l){
		o<<el;
		at++;
		if(!(at%nl))
			o<<endl;
	}
	return o;
}


#endif

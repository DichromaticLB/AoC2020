#ifndef INCLUDE_DAY23_HPP_
#define INCLUDE_DAY23_HPP_

#include<fstream>
#include<vector>
#include<map>
#include<list>
#include<unordered_map>
#include<string>
#include<iostream>
#include<utility>


struct day23{

	struct node{
		node(uint64_t val){
			this->val=val;
			prev=next=nullptr;
		}

		bool operator<(const node& other) const{
			return val<other.val;
		}

		uint64_t val;
		node*prev,*next;
	};

	struct game{

		game(const string& s,uint64_t limit){
			nodes.reserve(limit);

			for(uint64_t e=1;e<=limit;e++){
				nodes.emplace_back(e);
			}

			for(uint64_t e=0;e<nodes.size();e++){
				nodes[e].next=&nodes[(e+1)%nodes.size()];
				nodes[e].prev=&nodes[(e+nodes.size()-1)%nodes.size()];
			}

			for(uint64_t e=0;e<s.size()-1;e++){
				nodes[s[e]-'0'-1].next=&nodes[s[e+1]-'0'-1];
				nodes[s[e+1]-'0'-1].prev=&nodes[s[e]-'0'-1];

			}

			nodes[s.back()-'0'-1].next=&nodes[s[0]-'0'-1];
			nodes[s[0]-'0'-1].prev=&nodes[s.back()-'0'-1];

			if(limit>s.size()){
				nodes.back().next=&nodes[s[0]-'0'-1];
				nodes[s[0]-'0'-1].prev=&nodes.back();
				nodes[s.back()-'0'-1].next=&nodes[s.size()];
				nodes[s.size()].prev=&nodes[s.back()-'0'-1];
			}

			current=&nodes[s[0]-'0'-1];

		}

		int adjustTarget(uint64_t a,uint64_t b, uint64_t c,
				uint64_t target, uint64_t upper){

			if(target==0)
				target=upper;

			while(target==a||target==b||target==c){
				target--;
				if(target==0)
					target=upper;
			}

			return target;
		}

		void iterate(){
			node* pickUp=current->next;
			node* connect=pickUp->next->next->next;

			current->next=connect;
			connect->prev=current;

			uint64_t a=pickUp->val,b=pickUp->next->val,c=pickUp->next->next->val;
			uint64_t target=adjustTarget(a,b,c,current->val-1,nodes.size());

			node* it=current,*after;

			it=&nodes[target-1];

			after=it->next;
			it->next=pickUp;
			pickUp->prev=it;
			after->prev=pickUp->next->next;
			pickUp->next->next->next=after;
			current=current->next;

		}


		uint64_t label(){
			uint64_t result=0;
			node*n=current;

			while(n->val!=1)
				n=n->next;

			n=n->next;

			while(n->val!=1)
			{
				result*=10;
				result+=n->val;
				n=n->next;
			}

			return result;

		}

		node* current;
		vector<node> nodes;
	};

	day23(const string& s):g(s,9),g2(s,1000000){

	}

	void getResult1(){
		for(uint64_t i=0;i<100;i++){
			g.iterate();
		}

		cout<<"Label after first 100 iterations "<<g.label()<<endl;
	}

	void getResult2(){
		for(uint64_t i=0;i<10000010;i++){
			g2.iterate();
		}

		auto cup1=&g2.nodes[0];
				cout<<"Label after first 10*1000*1000 iterations "<<
						cup1->next->val*cup1->next->next->val<<endl;

	}

	game g,g2;

};



#endif

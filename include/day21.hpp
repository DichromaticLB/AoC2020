#ifndef INCLUDE_DAY21_HPP_
#define INCLUDE_DAY21_HPP_

#include<fstream>
#include<vector>
#include<map>
#include<unordered_map>
#include<string>
#include<iostream>
#include<utility>

struct day21{

	struct recipe{

		recipe(fstream&e){
			string s;
			e>>s;
			while(s!="(contains")
			{
				ingredients.insert(s);
				e>>s;
			}

			e>>s;

			while(s.back()!=')'){
				s.pop_back();
				allergens.insert(s);
				e>>s;
			}
			s.pop_back();
			allergens.insert(s);
			e.ignore();
		}

		set<string> ingredients;
		set<string> allergens;

	};

	day21(const string& filename){
		fstream e(filename);

		while(e.peek()!=EOF){
			recipes.emplace_back(e);
		}

	}

	void getResult1(){

		for(auto &recipe:recipes){
			for(auto& allergen:recipe.allergens){
				if(!possibleAllergens.count(allergen))
					possibleAllergens[allergen].insert(
							recipe.ingredients.begin(),
							recipe.ingredients.end());
				else
				{
					vector<string> buffer(max(
							recipe.ingredients.size(),
							possibleAllergens[allergen].size()));

					auto end=set_intersection(
							recipe.ingredients.begin(),recipe.ingredients.end(),
							possibleAllergens[allergen].begin(),possibleAllergens[allergen].end(),buffer.begin());

					possibleAllergens[allergen].clear();
					possibleAllergens[allergen].insert(buffer.begin(),end);
				}

			}
		}

		unsigned prev=0,e=accumulate(possibleAllergens.begin(),possibleAllergens.end(),0,[](unsigned acum,const auto&e){
			return acum+(e.second.size()==1?1:0);
		});

		set<string> allCandidates;
		for(auto&v:possibleAllergens)
			allCandidates.insert(v.second.begin(),v.second.end());

		unsigned count=0;
		for(auto&recipe:recipes)
			for(auto&ingredient:recipe.ingredients)
			{
				if(!allCandidates.count(ingredient))
					count++;
			}

		cout<<count<<" ingredients won't contain allergens for sure"<<endl;

	}

	void getResult2(){
		map<string,set<string>> possibleAllergens=this->possibleAllergens;
		map<string,string> a2f;
		set<string> toRemove;

		while(a2f.size()!=possibleAllergens.size())
		{
			for(auto&v:possibleAllergens)
			{
				if(v.second.size()==1)
				{
					a2f[v.first]=*v.second.begin();
					toRemove.insert(a2f[v.first]);
				}
			}

			for(auto&v:toRemove)
				for(auto&vv:possibleAllergens)
					vv.second.erase(v);
			toRemove.clear();
		}

		cout<<"Foods with allergens: ";
		bool first=true;
		for(auto&food:a2f)
		{
			if(!first)
				cout<<",";
			cout<<food.second;
			first=false;
		}

		cout<<endl;
	}

	vector<recipe> recipes;
	map<string,set<string>> possibleAllergens;
};


#endif

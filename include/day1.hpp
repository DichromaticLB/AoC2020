#ifndef DAY1HPP
#define DAY1HPP

using namespace std;

#include<string>
#include<vector>
#include<cstdint>
#include<fstream>
#include<iostream>

	struct day1{

		day1(const string &input){
			ifstream e(input);
			uint32_t n;

			e>>n;

			while(!e.fail()){
				numbers.push_back(n);
				e>>n;
			}

		}

		void getResult1(){
			for(const auto i1:numbers)
				for(const auto i2:numbers)
					if(i1+i2==2020){
						cout<<i1*i2<<endl;
						return;
					}
		}

		void getResult2(){
			for(const auto i1:numbers)
				for(const auto i2:numbers)
					for(const auto i3:numbers)
						if(i1+i2+i3==2020){
							cout<<i1*i2*i3<<endl;
							return;
						}
				}


		vector<uint32_t> numbers;
	};


#endif

#ifndef INCLUDE_UTIL_HPP_
#define INCLUDE_UTIL_HPP_

#include<vector>
#include<cstdint>
#include<map>

namespace util{
	using namespace std;

	//map of (first ^ second)
	map<uint64_t,uint64_t> factor(uint64_t t){
		uint64_t lim=t/2;
		map<uint64_t,uint64_t> res;
		for(uint64_t at=2;at<lim;at++){
			if((t%at==0)){
				while(t%at==0){
					res[at]++;
					t/=at;
				}
				lim=t/2;
			}
		}
		if(t>1)
			res[t]++;
		return res;
	}

	template<class T>
	T tpow(T a,T b){
		T res=1;

		while(b--)
			res*=a;

		return res;

	}

	uint64_t lcm(const vector<uint64_t>& m){
		map<uint64_t,uint64_t> res;
		for(auto& v:m){
			for(auto e:factor(v)){
				if(!res.count(e.first)||res[e.first]<e.second)
					res[e.first]=e.second;
			}
		}
		uint64_t ret=1;

		for(auto v:res)
			ret*=tpow(v.first,v.second);

		return ret;
	}

}






#endif

#include "solver.h"

namespace solver {
	void solve(const InputData&, Solution&){

	}
	long long eval(Solution& sol){
		long long res = 0;
		for (int i=0; i < (int)sol.slides.size() - 1; ++i){
			Slide s1 = sol.slides[i];
			Slide s2 = sol.slides[i+1];
			int inter = 0;
			for (int t1 : s1.tags){
				if (s2.tags.count(t1)){
					++inter;
				}
			}
			res += std::min(std::min(inter,(int)s1.tags.size()-inter),(int)s2.tags.size()-inter);
		}
		return res;
	}
}

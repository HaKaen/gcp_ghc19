#include "solver.h"
#include <cassert>

namespace solver {
	void solve(const InputData&, Solution&){

	}
	int eval(Solution& sol){
		int res = 0;
		sol.evals.resize(sol.slides.size()-1);
		for (int i=0; i < (int)sol.slides.size() - 1; ++i){
			Slide s1 = sol.slides[i];
			Slide s2 = sol.slides[i+1];
			int inter = 0;
			for (int t1 : s1.tags){
				if (s2.tags.count(t1)){
					++inter;
				}
			}
			sol.evals[i] = std::min(std::min(inter,(int)s1.tags.size()-inter),(int)s2.tags.size()-inter);
			res += sol.evals[i];
		}
		return res;
	}
	int lazyeval(Solution& sol, int a, int b){
		assert(a<=b);
		assert(sol.evals.size() == sol.slides.size()-1);
		int old_eval = 0;
		int new_eval = 0;
		for (int i=std::max(a-1,0); i < std::min((int)sol.slides.size() - 1, b); ++i){
			Slide s1 = sol.slides[i];
			Slide s2 = sol.slides[i+1];
			int inter = 0;
			for (int t1 : s1.tags){
				if (s2.tags.count(t1)){
					++inter;
				}
			}
			old_eval += sol.evals[i];
			sol.evals[i] = std::min(std::min(inter,(int)s1.tags.size()-inter),(int)s2.tags.size()-inter);
			new_eval += sol.evals[i];
		}
		return new_eval - old_eval;
	}
}

#include "solver.h"
#include <cassert>
#include <iostream>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <random>

namespace solver {

	int evalSlides(const Slide& s1, const Slide& s2){
		int inter = 0;
		for (int t1 : s1.tags){
			if (s2.tags.count(t1)){
				++inter;
			}
		}
		return std::min(std::min(inter,(int)s1.tags.size()-inter),(int)s2.tags.size()-inter);
	}

	int eval(Solution& sol, bool redo){
		if (redo){
			for (int i=0; i < (int)sol.evals.size(); ++i){
				sol.evals[i] = evalSlides(sol.slides[i], sol.slides[i+1]);
			}
		}
		return std::accumulate(sol.evals.begin(), sol.evals.end(), 0);
	}

	int lazyeval(Solution& sol, int a){
		int nb_slides = sol.slides.size();
		int old_eval = 0;
		int new_eval = 0;
		for (int i=std::max(a-1,0); i <= std::min(nb_slides-1, a); ++i){
			old_eval += sol.evals[i];
			sol.evals[i] = evalSlides(sol.slides[i], sol.slides[i+1]);
			new_eval += sol.evals[i];
		}
		return new_eval - old_eval;
	}

	void greedy1(const InputData& data, Solution& sol){

		auto updateTags = [&data](Slide& slide){
			slide.tags.clear();
			slide.tags.insert(data.photos[slide.p1].tags.begin(),data.photos[slide.p1].tags.end());
			if (slide.p2 >= 0)
				slide.tags.insert(data.photos[slide.p2].tags.begin(),data.photos[slide.p2].tags.end());
		};

		auto choseNextH = [&data](int i){
			return data.horizontal[i+1];
		};

		auto choseNext2V= [&data](int i){
			return std::make_pair(data.vertical[i+1],data.vertical[i+2]);
		};

		int nb_slides = data.horizontal.size()+data.vertical.size()/2;
		sol.slides.resize(nb_slides);
		sol.evals.resize(nb_slides-1,0);
		int h = -1;
		int v = -1;
		for (int s = 0; s < nb_slides; ++s){
			if (h < (int)data.horizontal.size() -1){
				// take 1 horizontal photo
				sol.slides[s].p1 = choseNextH(h);
				h++;
			}
			else if (v < (int)data.vertical.size() - 2) {
				// take 2 vertical photos
				std::tie(sol.slides[s].p1, sol.slides[s].p2) = choseNext2V(v);
				v += 2;
			}
			updateTags(sol.slides[s]);
			if (s){
				sol.evals[s-1] = evalSlides(sol.slides[s-1], sol.slides[s]);
			}
		}
	}

	void greedy2(const InputData& data, Solution& sol){

		std::vector<int> vertical = data.vertical;
		std::sort(vertical.begin(),vertical.end(), [&data](int a, int b){
			return data.photos[a].tags.size() < data.photos[b].tags.size();
		});

		auto updateTags = [&data](Slide& slide){
			slide.tags.clear();
			slide.tags.insert(data.photos[slide.p1].tags.begin(),data.photos[slide.p1].tags.end());
			if (slide.p2 >= 0)
				slide.tags.insert(data.photos[slide.p2].tags.begin(),data.photos[slide.p2].tags.end());
		};

		int nb_slides = (int)data.horizontal.size()+(int)vertical.size()/2;
		std::vector<Slide> allslides(nb_slides);
		for (int v=0; v<(int)vertical.size()/2; ++v){
//			allslides[v].p1 = vertical[v*2];
//			allslides[v].p2 = vertical[v*2+1];
			allslides[v].p1 = vertical[v];
			allslides[v].p2 = vertical[vertical.size()-1-v];
			updateTags(allslides[v]);
		}
		for (int h=0; h<(int)data.horizontal.size(); ++h){
			allslides[vertical.size()/2+h].p1 = data.horizontal[h];
			updateTags(allslides[vertical.size()/2+h]);
		}

		auto choseNextS = [&data](Slide& prev, std::vector<bool>& isin, std::vector<Slide>& slides, Slide& best_slide, int& eval){
			std::vector<int> evals(slides.size());
//#pragma omp parallel for
			for (int s=0; s<(int)slides.size(); ++s){
				if (isin[s]){
					evals[s] = -1;
					continue;
				}
				evals[s] = evalSlides(prev, slides[s]);
			}
			auto maxeval = std::max_element(evals.begin(), evals.end());
			auto ind = std::distance(evals.begin(), maxeval);
			isin[ind] = true;
			best_slide = slides[ind];
			eval = *maxeval;
		};

		std::vector<bool> isin(nb_slides);
		sol.slides.resize(nb_slides);
		sol.evals.resize(nb_slides-1,0);

		sol.slides[0] = allslides[0];
		isin[0] = true;
		for (int s = 1; s < nb_slides; ++s){
			choseNextS(sol.slides[s-1], isin, allslides, sol.slides[s],sol.evals[s-1]);
		}
	}

	void local_search(const InputData& data, Solution& sol, int nb_iter, int nb_splits){

		auto try_swap = [&data,&sol](std::mt19937& gen, int begin, int end){
			if (begin >= end) return;
			std::uniform_int_distribution<std::size_t> dist(begin, end);
			int a = dist(gen);
			int b = dist(gen);
			while (b == a){
				b = dist(gen);
			}
			Slide tmp = sol.slides[a];
			sol.slides[a] = sol.slides[b];
			sol.slides[b] = tmp;
			int change = lazyeval(sol,a) + lazyeval(sol,b);
			if (change < 0){
				sol.slides[b] = sol.slides[a];
				sol.slides[a] = tmp;
				lazyeval(sol,a);lazyeval(sol,b);
			}
		};

		int split_size = sol.slides.size()/nb_splits;
#pragma omp parallel for
		for (int split=0; split < nb_splits; ++split){
			std::mt19937 generator;
			generator.seed(split);
			for (int iter=0; iter < nb_iter; ++iter){
				try_swap(generator,split*split_size,(split+1)*split_size-2); // -2 for concurrency
			}
		}

	}

}

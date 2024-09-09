#ifndef INCLUDE_SOLVER_H_
#define INCLUDE_SOLVER_H_

#include "data.h"

namespace solver {
	int evalSlides(const Slide&, const Slide&);
	int eval(Solution&, bool redo = false);
	int lazyeval(Solution&, int);
	void greedy1(const InputData&, Solution&);
	void greedy2(const InputData&, Solution&);
	void local_search(const InputData& , Solution& , int nb_iter, int nb_splits);
}

#endif /* INCLUDE_SOLVER_H_ */

#ifndef INCLUDE_SOLVER_H_
#define INCLUDE_SOLVER_H_

#include "data.h"

namespace solver {
	void solve(const InputData&, Solution&);
	int eval(Solution&);
	int lazyeval(Solution&, int, int);
}

#endif /* INCLUDE_SOLVER_H_ */

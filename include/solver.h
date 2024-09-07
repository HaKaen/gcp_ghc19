#ifndef INCLUDE_SOLVER_H_
#define INCLUDE_SOLVER_H_

#include "data.h"

namespace solver {
	void solve(const InputData&, Solution&);
	long long eval(Solution&);
}

#endif /* INCLUDE_SOLVER_H_ */

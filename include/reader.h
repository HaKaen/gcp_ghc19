#ifndef INCLUDE_READER_H_
#define INCLUDE_READER_H_

#include "data.h"

namespace reader {
	void read(std::string, InputData&);
	void dump(std::ostream&, InputData&);
	void stats(std::ostream&, InputData&);
}

#endif /* INCLUDE_READER_H_ */

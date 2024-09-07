#ifndef INCLUDE_WRITER_H_
#define INCLUDE_WRITER_H_

#include "data.h"

namespace writer {
	void write(std::string, const Solution&);
	void write(std::ostream&, const Solution&);
}

#endif /* INCLUDE_WRITER_H_ */

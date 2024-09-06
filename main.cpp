#include <iostream>
#include <fstream>
#include "data.h"
#include "config.h"

// decl methods
// impl in cpp
namespace reader {
	void read(std::string, InputData&);
}
namespace solver {
	long long solve(const InputData&, Solution&);
}
namespace writer {
	void write(std::string, const Solution&);
	void write(std::ostream&, const Solution&);
}

int main(int argc, char const* argv[])
{
	if (argc < 2){
		std::cout << "Version " << PROJECT_VERSION << std::endl;
		std::cout << "Usage: " << argv[0] << " arguments" << std::endl;
		return 0;
	}

    std::string filename(argv[1]);

    InputData data;
    Solution s;

    reader::read(filename, data);
    long long eval = solver::solve(data, s);

    writer::write(filename, s);
    writer::write(std::cout, s);

    std::cerr << "eval " << filename << " = " << eval << std::endl;

    return 0;
}

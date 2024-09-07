#include <iostream>
#include <fstream>
#include "reader.h"
#include "solver.h"
#include "writer.h"
#include "config.h"

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
//    reader::dump(std::cerr, data);
    solver::solve(data, s);

    writer::write(filename, s);
//    writer::write(std::cout, s);

    std::cerr << "eval " << filename << " = " << solver::eval(s) << std::endl;

    return 0;
}

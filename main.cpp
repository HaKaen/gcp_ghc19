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
		return 0;
	}

    std::string filename(argv[1]);

    InputData data;
    Solution sol;

    reader::read(filename, data);
//    reader::dump(std::cerr, data);
    solver::solve(data, sol);

    writer::write(filename+".out", sol);
//    writer::write(std::cout, sol);

    std::cerr << "eval " << filename << " = " << solver::eval(sol) << std::endl;

    return 0;
}

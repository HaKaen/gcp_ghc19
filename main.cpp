#include <iostream>
#include <fstream>
#include "reader.h"
#include "solver.h"
#include "writer.h"
#include "config.h"
#include <chrono>

int main(int argc, char const* argv[])
{
	if (argc < 2){
		std::cout << "Version " << PROJECT_VERSION << std::endl;
		return 0;
	}
	auto start = std::chrono::system_clock::now();
    std::string filename(argv[1]);

    InputData data;
    reader::read(filename, data);
//    reader::stats(std::cerr, data);


    /*
     * INIT SOLUTION
     */
    Solution sol;
    if (argc == 3){
    	std::string warmstart(argv[2]);
    	writer::read(warmstart, sol, data);
    	std::cerr << "warmstart with " << warmstart << ", found eval = " << solver::eval(sol, true) << std::endl;
    }
    else {
    	solver::greedy2(data, sol);
    }

    /*
     * LOCAL SEARCH
     */
    int init_eval = solver::eval(sol);
    solver::local_search(data,sol,1<<20,2);
    int eval2 = solver::eval(sol);
    solver::local_search(data,sol,1<<19,4);
    int eval3 = solver::eval(sol);
    solver::local_search(data,sol,1<<18,8);

    int eval = solver::eval(sol);
    writer::write(filename+".out."+std::to_string(eval), sol);

	auto end = std::chrono::system_clock::now();
    std::cerr << "eval " << filename << " = " << eval << "(+" << eval2-init_eval << ", +" << eval3-eval2 << ", +" << eval-eval3 << ")" << std::endl;
	std::cerr << "elapsed " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
    return 0;
}

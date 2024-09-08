#include "writer.h"
#include <iostream>
#include <fstream>

namespace writer {
	void write(std::string path, const Solution& solution){
		std::ofstream outputFile(path);
		outputFile << solution.slides.size();
		for (auto slide : solution.slides){
			outputFile  << std::endl << slide.p1;
			if (slide.p2 >= 0){
				outputFile << " " << slide.p2;
			}
		}
	}
	void write(std::ostream& stream, const Solution& solution){
		stream << solution.slides.size();
		for (auto slide : solution.slides){
			stream << std::endl << slide.p1;
			if (slide.p2 >= 0){
				stream << " " << slide.p2;
			}
		}
	}
	void read(std::string path, Solution& solution, const InputData& data){
		std::ifstream inputFile(path);
		int n,p1,p2;
		inputFile >> n;
		solution.slides.clear();
		solution.slides.resize(n);
		for (int i=0; i<n; ++i){
			inputFile >> p1;
			if (data.photos[p1].isVertical){
				inputFile >> p2;
				solution.slides[i].p2 = p2;
			}
			solution.slides[i].p1 = p1;
		}
	}
}

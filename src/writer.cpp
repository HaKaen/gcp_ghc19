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
}

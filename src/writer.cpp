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
		auto updateTags = [&data](Slide& slide){
			slide.tags.clear();
			slide.tags.insert(data.photos[slide.p1].tags.begin(),data.photos[slide.p1].tags.end());
			if (slide.p2 >= 0)
				slide.tags.insert(data.photos[slide.p2].tags.begin(),data.photos[slide.p2].tags.end());
		};

		std::ifstream inputFile(path);
		int n;
		inputFile >> n;
		solution.slides.resize(n);
		solution.evals.resize(n-1);
		for (int i=0; i<n; ++i){
			int p1,p2;
			inputFile >> p1;
			solution.slides[i].p1 = p1;
			if (data.photos[p1].is_vertical){
				inputFile >> p2;
				solution.slides[i].p2 = p2;
			}
			updateTags(solution.slides[i]);
		}
	}
}

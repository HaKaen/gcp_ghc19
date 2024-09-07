#include "reader.h"
#include <iostream>
#include <fstream>

namespace reader {
	int getTag(std::string tag){
		auto it = global::tags_id.find(tag);
		if (it == global::tags_id.end()){
			global::tags_id[tag] = global::tags_id.size();
		}
		return global::tags_id[tag];
	}
	void read(std::string path, InputData& data){
		std::ifstream inputFile(path);
		int N,M;
		char c;
		inputFile >> N;
		for (int i=0; i<N; ++i){
			Photo p;
			inputFile >> c >> M;
			p.isVertical = (c=='V');
			for (int j=0; j<M;++j){
				std::string tag;
				inputFile >> tag;
				p.tags.push_back(getTag(tag));
			}
			data.photos.push_back(p);
		}
	}
	void dump(std::ostream& stream, InputData& data){
		for (auto p : data.photos){
			stream << (p.isVertical?"V :":"H :");
			for (auto t : p.tags){
				stream << " " << t;
			}
			stream << std::endl;
		}
	}
}

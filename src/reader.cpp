#include "reader.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <cmath>
#include <algorithm>

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
		if (path.find("b.in") != std::string::npos) {
			global::tags_id.reserve(840000);
		}
		int N,M;
		char c;
		inputFile >> N;
		for (int i=0; i<N; ++i){
			Photo p;
			inputFile >> c >> M;
			p.is_vertical = (c=='V');
			for (int j=0; j<M;++j){
				std::string tag;
				inputFile >> tag;
				p.tags.push_back(getTag(tag));
			}
			data.photos.push_back(p);
			if (p.is_vertical)
				data.vertical.push_back(i);
			else
				data.horizontal.push_back(i);
		}
	}
	void dump(std::ostream& stream, InputData& data){
		for (auto p : data.photos){
			stream << (p.is_vertical?"V :":"H :");
			for (auto t : p.tags){
				stream << " " << t;
			}
			stream << std::endl;
		}
	}
	void stats(std::ostream& stream, InputData& data){
		int h = 0;
		long sum = 0;
		long hsum = 0;
		long vsum = 0;
		int tagsm = 999;
		int tagsM = 0;
		int htagsm = 999;
		int htagsM = 0;
		int vtagsm = 999;
		int vtagsM = 0;
		for (auto p : data.photos){
			if (p.is_vertical){
				vsum += p.tags.size();
				vtagsm = std::min(vtagsm, (int)p.tags.size());
				vtagsM = std::max(vtagsM, (int)p.tags.size());
			}
			else {
				hsum += p.tags.size();
				htagsm = std::min(htagsm, (int)p.tags.size());
				htagsM = std::max(htagsM, (int)p.tags.size());
				++h;
			}
			sum += p.tags.size();
			tagsm = std::min(tagsm, (int)p.tags.size());
			tagsM = std::max(tagsM, (int)p.tags.size());

		}
		int maxb = 0;
		int minb = sum;
		for (int b=0; b<(int)global::tags_id.bucket_count(); ++b){
			maxb = std::max((int)global::tags_id.bucket_size(b),maxb);
			minb = std::min((int)global::tags_id.bucket_size(b),minb);
		}

		stream << "--------STATS--------" << std::endl;
		stream << "NB PHOTO       : " << data.photos.size() << std::endl;
		stream << "NB TAGS        : " << global::tags_id.size() << std::endl;
		stream << "NB BUCKETS     : " << global::tags_id.bucket_count() << std::endl;
		stream << "LOAD FACTOR    : " << global::tags_id.load_factor() << std::endl;
		stream << "MIN BUCKET     : " << minb << std::endl;
		stream << "MAX BUCKET     : " << maxb << std::endl;
		stream << "VERTICAL PIC   : " << data.photos.size()-h << std::endl;
		stream << "HORIZONTAL PIC : " << h << std::endl;
		stream << "NB TAG   (min/moy/max) : " << tagsm << "/" << (double)sum/data.photos.size() << "/" << tagsM << std::endl;
		stream << "NB TAG V (min/moy/max) : " << vtagsm << "/" << (double)vsum/data.vertical.size() << "/" << vtagsM << std::endl;
		stream << "NB TAG H (min/moy/max) : " << htagsm << "/" << (double)hsum/data.horizontal.size() << "/" << htagsM << std::endl;
		stream << "---------END---------" << std::endl;
	}
}

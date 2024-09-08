#ifndef SRC_DATA_H_
#define SRC_DATA_H_

#include <vector>
#include <string>
#include <unordered_map>
#include <set>

namespace global{
	extern std::unordered_map<std::string, int> tags_id; // 10^5 * 100 * 10 < INT_MAX
}

struct Photo {
	bool isVertical = false;
	std::vector<int> tags;
};

struct Slide {
	int p1 = -1;
	int p2 = -1;
	std::set<int> tags;
};

struct InputData {
	std::vector<Photo> photos;
};

struct Solution {
	std::vector<Slide> slides;
	std::vector<int> evals;
};

#endif /* SRC_DATA_H_ */

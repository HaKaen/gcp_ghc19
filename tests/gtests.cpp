#include <gtest/gtest.h>
#include <sstream>
#include "reader.h"
#include "solver.h"
#include "writer.h"
#include "config.h"

TEST(reader, read) {
	InputData data;
	std::string filename = std::string(PROJECT_DATA_DIR) + "/a.in";
	reader::read(filename, data);
	EXPECT_EQ(data.photos.size(),4);
	EXPECT_EQ(data.photos[0].is_vertical,false);
	EXPECT_EQ(data.photos[1].is_vertical,true);
	EXPECT_EQ(data.photos[2].is_vertical,true);
	EXPECT_EQ(data.photos[3].is_vertical,false);
	EXPECT_EQ(data.vertical.size(),2);
	EXPECT_EQ(data.horizontal.size(),2);
	EXPECT_EQ(data.photos[0].tags.size(),3);
	EXPECT_EQ(data.photos[1].tags.size(),2);
	EXPECT_EQ(data.photos[2].tags.size(),2);
	EXPECT_EQ(data.photos[3].tags.size(),2);
}

TEST(solver, eval) {
	Solution sol;
	Slide s1,s2,s3;
	s1.tags = {0,1,2};
	s2.tags = {5,0};
	s3.tags = {3,4,5};
	sol.slides = {s1, s2, s3};
	sol.evals.resize(2,0);
	sol.evals[0] = solver::evalSlides(s1,s2);
	sol.evals[1] = solver::evalSlides(s2,s3);

	EXPECT_EQ(sol.evals[0],1);
	EXPECT_EQ(sol.evals[1],1);
	EXPECT_EQ(solver::eval(sol),2);
	int lazyeval = solver::lazyeval(sol,0);
	EXPECT_EQ(lazyeval,0);
	EXPECT_EQ(sol.evals[0],1);
	EXPECT_EQ(sol.evals[1],1);
	sol.slides[0].tags.insert(4);
	sol.slides[1].tags.insert(1);
	sol.slides[1].tags.insert(3);
	lazyeval = solver::lazyeval(sol,1);
	EXPECT_EQ(lazyeval,1);
	EXPECT_EQ(sol.evals[0],2);
	EXPECT_EQ(sol.evals[1],1);
}

TEST(writer, dump) {
	Solution sol;
	sol.slides.push_back({0});
	sol.slides.push_back({3});
	sol.slides.push_back({1,2});

	std::stringstream ss;
	writer::write(ss, sol);
	EXPECT_EQ(ss.str(),"3\n0\n3\n1 2");
}

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "chargingcurrent-range.h"

TEST_CASE("detect the ranges in the given input list") {
	std::vector<Range> listofRanges = {};
	std::vector<int> inputList = { 4, 5 };
	listofRanges = computeCurrentRanges(inputList);
	REQUIRE(listofRanges.size() == 1);
}

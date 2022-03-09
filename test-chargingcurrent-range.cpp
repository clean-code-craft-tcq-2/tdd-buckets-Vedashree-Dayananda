#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "chargingcurrent-range.h"

TEST_CASE("detect the ranges in the given input list with 2 elements") {
	std::vector<Range> listofRanges = {};
	std::vector<int> inputList = { 4, 5 };
	listofRanges = computeCurrentRanges(inputList);
	REQUIRE(listofRanges.size() == 1);
	REQUIRE(listofRanges[0].lowerLimit == 4);
	REQUIRE(listofRanges[0].upperLimit == 5);
	REQUIRE(listofRanges[0].numOfReadingsInRange == 2);
}

TEST_CASE("detect the ranges in the unsorted input list ") {
	std::vector<Range> listofRanges = {};
	std::vector<int> inputList = { 3, 3, 5, 4, 10, 11, 12 };
	listofRanges = computeCurrentRanges(inputList);
	REQUIRE(listofRanges.size() == 2);
}

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "chargingcurrent-range.h"

TEST_CASE("detect the ranges in the given input list with 2 elements") {
	std::vector<Range> listofRanges = {};
	std::vector<double> inputList = { 4, 5 };
	listofRanges = computeCurrentRanges(inputList);
	REQUIRE(listofRanges.size() == 1);
	REQUIRE(listofRanges[0].lowerLimit == 4);
	REQUIRE(listofRanges[0].upperLimit == 5);
	REQUIRE(listofRanges[0].numOfReadingsInRange == 2);
}

TEST_CASE("detect the ranges in the unsorted input list ") {
	std::vector<Range> listofRanges = {};
	std::vector<double> inputList = { 3, 3, 5, 4, 10, 11, 12 };
	listofRanges = computeCurrentRanges(inputList);
	REQUIRE(listofRanges.size() == 2);
	REQUIRE(listofRanges[0].lowerLimit == 3);
	REQUIRE(listofRanges[0].upperLimit == 5);
	REQUIRE(listofRanges[0].numOfReadingsInRange == 4);
	
	REQUIRE(listofRanges[1].lowerLimit == 10);
	REQUIRE(listofRanges[1].upperLimit == 12);
	REQUIRE(listofRanges[1].numOfReadingsInRange == 3);
}

TEST_CASE("return empty list of  the ranges when no readings are provided") {
	std::vector<Range> listofRanges = {};
	std::vector<double> inputList = {};
	listofRanges = computeCurrentRanges(inputList);
	REQUIRE(listofRanges.empty() == true);
}

TEST_CASE("verify format of data printed") {
	std::vector<Range> listofRanges = { { 1, 7, 3 }, { 18, 25, 8 } };
	std::string expectedOutputText = "Range, Reading \n";
	for (int i = 0; (size_t)i < listofRanges.size(); i++)
		expectedOutputText += std::to_string(listofRanges[i].lowerLimit) + "-" + std::to_string(listofRanges[i].upperLimit) + "," + std::to_string(listofRanges[i].numOfReadingsInRange) + "\n";
	std::string actualOutputText = formatOutputToCsv(listofRanges);
	REQUIRE(expectedOutputText.compare(actualOutputText) == 0);
}

TEST_CASE("detect the ranges in the given input list with 12 bit  ADC elements") {
	std::vector<Range> listofRanges = {};
	std::vector<double> inputList = { 1146, 1806 , 3065,3450,3650};
	listofRanges = computeCurrentRangesFromADCReading(inputList, 12);
	REQUIRE(listofRanges.size() == 2);
	REQUIRE(listofRanges[0].lowerLimit == 3);
	REQUIRE(listofRanges[0].upperLimit == 4);
	REQUIRE(listofRanges[0].numOfReadingsInRange == 2);
	REQUIRE(listofRanges[1].lowerLimit == 7);
	REQUIRE(listofRanges[1].upperLimit == 9);
	REQUIRE(listofRanges[1].numOfReadingsInRange == 3);
}

TEST_CASE("return empty list of  the ranges when negative readings are provided for 12 bit ADC") {
	std::vector<Range> listofRanges = {};
	std::vector<double> inputList = { 1146, 1806, 3065, 3450, 3650 , -1146 };
	listofRanges = computeCurrentRangesFromADCReading(inputList, 12);
	REQUIRE(listofRanges.empty() == true);
}

TEST_CASE("return empty list of  the ranges when out of range readings are provided for 12 bit ADC") {
	std::vector<Range> listofRanges = {};
	std::vector<double> inputList = { 1146, 1806, 3065, 3450, 3650, 4095};
	listofRanges = computeCurrentRangesFromADCReading(inputList, 12);
	REQUIRE(listofRanges.empty() == true);
}

TEST_CASE("detect the ranges in the given input list with 10 bit  ADC elements") {
	std::vector<Range> listofRanges = {};
	std::vector<double> inputList = { 0, 1022, 1000, 100 , 900 };
	listofRanges = computeCurrentRangesFromADCReading(inputList, 10);
	REQUIRE(listofRanges.size() == 2);
	REQUIRE(listofRanges[0].lowerLimit == 11);
	REQUIRE(listofRanges[0].upperLimit == 12);
	REQUIRE(listofRanges[0].numOfReadingsInRange == 2);
	REQUIRE(listofRanges[1].lowerLimit == 14);
	REQUIRE(listofRanges[1].upperLimit == 15);
	REQUIRE(listofRanges[1].numOfReadingsInRange == 3);

}

TEST_CASE("return empty list of  the ranges when negative readings are provided for 10 bit ADC") {
	std::vector<Range> listofRanges = {};
	std::vector<double> inputList = { 0, -1022, 1000, 100, 900 };
	listofRanges = computeCurrentRangesFromADCReading(inputList, 10);
	REQUIRE(listofRanges.empty() == true);
}

TEST_CASE("return empty list of  the ranges when out of range readings are provided for 10 bit ADC") {
	std::vector<Range> listofRanges = {};
	std::vector<double> inputList = { 0, 1024, 1000, 100, 900 };
	listofRanges = computeCurrentRangesFromADCReading(inputList, 10);
	REQUIRE(listofRanges.empty() == true);
}

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "chargingcurrent-range.h"

TEST_CASE("detect the ranges in the given input list with 2 elements") {
	std::vector<Range> listofRanges1 = {};
	std::vector<double> inputList1 = { 4, 5 };
	listofRanges1 = computeCurrentRanges(inputList1);
	REQUIRE(listofRanges1.size() == 1);
	REQUIRE(listofRanges1[0].lowerLimit == 4);
	REQUIRE(listofRanges1[0].upperLimit == 5);
	REQUIRE(listofRanges1[0].numOfReadingsInRange == 2);
}

TEST_CASE("detect the ranges in the unsorted input list ") {
	std::vector<Range> listofRanges2 = {};
	std::vector<double> inputList2 = { 3, 3, 5, 4, 10, 11, 12 };
	listofRanges2 = computeCurrentRanges(inputList2);
	REQUIRE(listofRanges2.size() == 2);
	REQUIRE(listofRanges2[0].lowerLimit == 3);
	REQUIRE(listofRanges2[0].upperLimit == 5);
	REQUIRE(listofRanges2[0].numOfReadingsInRange == 4);
	
	REQUIRE(listofRanges2[1].lowerLimit == 10);
	REQUIRE(listofRanges2[1].upperLimit == 12);
	REQUIRE(listofRanges2[1].numOfReadingsInRange == 3);
}

TEST_CASE("return empty list of  the ranges when no readings are provided") {
	std::vector<Range> listofRanges3 = {};
	std::vector<double> inputList3 = {};
	listofRanges3 = computeCurrentRanges(inputList3);
	REQUIRE(listofRanges3.empty() == true);
}

TEST_CASE("verify format of data printed") {
	std::vector<Range> listofRanges4 = { { 1, 7, 3 }, { 18, 25, 8 } };
	std::string expectedOutputText = "Range, Reading \n";
	for (int i = 0; (size_t)i < listofRanges4.size(); i++)
		expectedOutputText += std::to_string(listofRanges4[i].lowerLimit) + "-" + std::to_string(listofRanges4[i].upperLimit) + "," + std::to_string(listofRanges4[i].numOfReadingsInRange) + "\n";
	std::string actualOutputText = formatOutputToCsv(listofRanges4);
	REQUIRE(expectedOutputText.compare(actualOutputText) == 0);
}

TEST_CASE("detect the ranges in the given input list with 12 bit  ADC elements") {
	std::vector<Range> listofRanges5 = {};
	std::vector<double> inputList5 = { 1146, 1806 , 3065,3450,3650};
	listofRanges5 = computeCurrentRangesFromADCReading(inputList5, 12);
	REQUIRE(listofRanges5.size() == 2);
	REQUIRE(listofRanges5[0].lowerLimit == 3);
	REQUIRE(listofRanges5[0].upperLimit == 4);
	REQUIRE(listofRanges5[0].numOfReadingsInRange == 2);
	REQUIRE(listofRanges5[1].lowerLimit == 7);
	REQUIRE(listofRanges5[1].upperLimit == 9);
	REQUIRE(listofRanges5[1].numOfReadingsInRange == 3);
}

TEST_CASE("return empty list of  the ranges when negative readings are provided for 12 bit ADC") {
	std::vector<Range> listofRanges6 = {};
	std::vector<double> inputList6 = { 1146, 1806, 3065, 3450, 3650 , -1146 };
	listofRanges6 = computeCurrentRangesFromADCReading(inputList6, 12);
	REQUIRE(listofRanges6.empty() == true);
}

TEST_CASE("return empty list of  the ranges when out of range readings are provided for 12 bit ADC") {
	std::vector<Range> listofRanges7 = {};
	std::vector<double> inputList7 = { 1146, 1806, 3065, 3450, 3650, 4095};
	listofRanges7 = computeCurrentRangesFromADCReading(inputList7, 12);
	REQUIRE(listofRanges7.empty() == true);
}

TEST_CASE("detect the ranges in the given input list with 10 bit  ADC elements") {
	std::vector<Range> listofRanges8 = {};
	std::vector<double> inputList8 = { 0, 1022, 1000, 100 , 900 };
	listofRanges8 = computeCurrentRangesFromADCReading(inputList8, 10);
	REQUIRE(listofRanges8.size() == 2);
	REQUIRE(listofRanges8[0].lowerLimit == 11);
	REQUIRE(listofRanges8[0].upperLimit == 12);
	REQUIRE(listofRanges8[0].numOfReadingsInRange == 2);
	REQUIRE(listofRanges8[1].lowerLimit == 14);
	REQUIRE(listofRanges8[1].upperLimit == 15);
	REQUIRE(listofRanges8[1].numOfReadingsInRange == 3);

}

TEST_CASE("return empty list of  the ranges when negative readings are provided for 10 bit ADC") {
	std::vector<Range> listofRanges9 = {};
	std::vector<double> inputList9 = { 0, -1022, 1000, 100, 900 };
	listofRanges9 = computeCurrentRangesFromADCReading(inputList9, 10);
	REQUIRE(listofRanges9.empty() == true);
}

TEST_CASE("return empty list of  the ranges when out of range readings are provided for 10 bit ADC") {
	std::vector<Range> listofRanges10 = {};
	std::vector<double> inputList10 = { 0, 1024, 1000, 100, 900 };
	listofRanges10 = computeCurrentRangesFromADCReading(inputList10, 10);
	REQUIRE(listofRanges10.empty() == true);
}

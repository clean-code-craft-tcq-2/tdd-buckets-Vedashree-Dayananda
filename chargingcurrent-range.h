#pragma once
#include <vector>

struct Range
{
	int lowerLimit;
	int upperLimit;
	int numOfReadingsInRange;
};

void displayRanges(std::vector<Range> listofRanges);
std::vector<Range> findRanges(std::vector<int> readingsList);
std::vector<Range> computeCurrentRanges(std::vector<int> readingsList);

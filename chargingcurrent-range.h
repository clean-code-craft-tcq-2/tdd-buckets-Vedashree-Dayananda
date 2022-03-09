#pragma once
#include <vector>

struct Range
{
	int lowerLimit;
	int upperLimit;
	int numOfReadingsInRange;
};

std::vector<Range> computeCurrentRanges(std::vector<int> readingsList);
void displayRanges(std::vector<Range> listofRanges);

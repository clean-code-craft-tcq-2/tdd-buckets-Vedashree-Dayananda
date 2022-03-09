#include "chargingcurrent-range.h"
#include <iostream>
using namespace std;

std::vector<Range> computeCurrentRanges(std::vector<int> readingsList)
{
	std::vector<Range> listofRanges = {};
	Range currentRange = {};
  
	currentRange.lowerLimit = readingsList[0];
	currentRange.upperLimit = readingsList[0];
	currentRange.numOfReadingsInRange = 0;
	for (std::vector<int>::iterator itr = readingsList.begin(); itr != readingsList.end(); itr++)
	{
		if (*itr - currentRange.upperLimit <= 1)
		{
			currentRange.upperLimit = *itr;
			currentRange.numOfReadingsInRange++;
		}
	}
	listofRanges.push_back(currentRange);
  return listofRanges;
}

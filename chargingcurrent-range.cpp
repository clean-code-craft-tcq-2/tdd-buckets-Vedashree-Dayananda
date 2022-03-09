#include "chargingcurrent-range.h"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void displayRanges(std::vector<Range> listofRanges)
{
	cout << "Range, Reading" << endl;
	for (int i = 0; i < listofRanges.size(); i++)
		cout << listofRanges[i].lowerLimit << "-" << listofRanges[i].upperLimit << ", " << listofRanges[i].numOfReadingsInRange << endl;
}

std::vector<Range> computeCurrentRanges(std::vector<int> readingsList)
{
	std::vector<Range> listofRanges = {};
	Range currentRange = {};
	
	if (readingsList.empty())
	{
		return {};
	}
	sort(readingsList.begin(), readingsList.end());
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
		else
		{
			listofRanges.push_back(currentRange);
			currentRange.lowerLimit = *itr;
			currentRange.upperLimit = *itr;
			currentRange.numOfReadingsInRange = 1;
		}
	}
	listofRanges.push_back(currentRange);
	displayRanges(listofRanges);
	return listofRanges;
}

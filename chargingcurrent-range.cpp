#include "chargingcurrent-range.h"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

std::map < int, int> MaximumLimitsMap = {
	{ 12, 4094 },
	{ 10, 1022 }
};

using funcptr = std::vector<double>(*)(std::vector<double>);

std::map < int, funcptr > ConverterFunctionMap = {
	{ 12, converterfor12BitSensor },
	{ 10, converterfor10BitSensor }
};

void printOnConsole(std::string outputText)
{
	cout << outputText;
}

std::string formatOutputToCsv(std::vector<Range> listofRanges)
{
	std::string outputText = "Range, Reading \n";
	for (int i = 0; (size_t)i < listofRanges.size(); i++)
		outputText += std::to_string(listofRanges[i].lowerLimit) + "-" + std::to_string(listofRanges[i].upperLimit) + "," + std::to_string(listofRanges[i].numOfReadingsInRange) + "\n";
	return outputText;
}
bool check_value_within_limit(double value, double max_value)
{
	if (value < 0 || value > max_value)
		return false;
	return true;

}

int validateReadings(std::vector<double> readingsList, int sensorType)
{
	for (std::vector<double>::iterator itr = readingsList.begin(); itr != readingsList.end(); itr++)
	{
		if (!check_value_within_limit(*itr, MaximumLimitsMap[sensorType]))
			return 0;
	}
	return 1;
}

std::vector<double> convertToAmps(std::vector<double> readingsList, int sensorType)
{
	funcptr coverterFunction = ConverterFunctionMap[sensorType];
	std::vector<double> outputList = (*coverterFunction)(readingsList);
	return outputList;
}

std::vector<double> converterfor12BitSensor(std::vector<double> readingsList)
{
	std::vector<double> convertedReadingsList12Bit = {};
	for (std::vector<double>::iterator itr1 = readingsList.begin(); itr != readingsList.end(); itr++)
	{
		double valueInAmp = ((10 * (*itr1)) / 4094);
		convertedReadingsList12Bit.push_back(round(valueInAmp));
	}
	return convertedReadingsList12Bit;
}

std::vector<double> converterfor10BitSensor(std::vector<double> readingsList)
{
	std::vector<double> convertedReadingsList10Bit = {};
	for (std::vector<double>::iterator itr2 = readingsList.begin(); itr != readingsList.end(); itr++)
	{
		double valueInAmp = (((*itr2) - 511.0) * 15.0 / 511.0);
		convertedReadingsList10Bit.push_back(abs(round(valueInAmp)));
	}
	return convertedReadingsList10Bit;
}

std::vector<Range> findRanges(std::vector<double> readingsList)
{
	std::vector<Range> listofRanges = {};
	Range currentRange = {};
	sort(readingsList.begin(), readingsList.end());
	currentRange.lowerLimit = readingsList[0];
	currentRange.upperLimit = readingsList[0];
	currentRange.numOfReadingsInRange = 0;
	for (std::vector<double>::iterator itr = readingsList.begin(); itr != readingsList.end(); itr++)
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
	return listofRanges;
}

std::vector<Range> computeCurrentRanges(std::vector<double> readingsList)
{
	std::vector<Range> listofRanges = {};
	
	if (readingsList.empty())
	{
		return {};
	}

	listofRanges = findRanges(readingsList);
	std::string outputText = formatOutputToCsv(listofRanges);
	printOnConsole(outputText);
	return listofRanges;
}

std::vector<Range> computeCurrentRangesFromADCReading(std::vector<double> readingsList , int sensorType)
{
	int validReadings = validateReadings(readingsList, sensorType);

	if (validReadings)
	{
		std::vector<double> convertedReadingsList = convertToAmps(readingsList, sensorType);
		std::vector<Range> listofRanges = computeCurrentRanges(convertedReadingsList);
		return listofRanges;
	}
	return{};
}

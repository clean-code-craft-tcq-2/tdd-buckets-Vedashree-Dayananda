#pragma once
#include <vector>
#include <string>
#include <map>

struct Range
{
	int lowerLimit;
	int upperLimit;
	int numOfReadingsInRange;
};

void printOnConsole(std::string outputText);
std::vector<Range> findRanges(std::vector<double> readingsList);
std::vector<Range> computeCurrentRanges(std::vector<double> readingsList);
std::string formatOutputToCsv(std::vector<Range> listofRanges);
int validateReadings(std::vector<double> readingsList, int sensorType);
std::vector<double> convertToAmps(std::vector<double> readingsList, int sensorType);
std::vector<double> converterfor12BitSensor(std::vector<double> readingsList);
std::vector<double> converterfor10BitSensor(std::vector<double> readingsList);

std::vector<Range> computeCurrentRangesFromADCReading(std::vector<double> readingsList, int sensorType);

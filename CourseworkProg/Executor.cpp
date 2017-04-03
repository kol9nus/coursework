#include "stdafx.h"
#include "Automat.h"
#include "Executor.h"
#include "Delta.h"
#include "OutResult.h"
#include <ctime>
#include <string>
#include <stdio.h>


Executor::Executor()
{
	currentPath = defineCurrentPath();
	string currentDate = getCurrentDate();
	maxFileName = currentDate + "max" + ".txt";
	offsetFileName = currentDate + "offset" + ".txt";
	createFileIfNotExists(maxFileName);
	createFileIfNotExists(offsetFileName);
}

Executor::~Executor()
{
}

string Executor::defineCurrentPath()
{
	char* buffer;

	// Get the current working directory: 
	if ((buffer = _getcwd(NULL, 0)) == NULL)
		perror("_getcwd error");
	string result(buffer);
	return result;
}

void Executor::createFileIfNotExists(string filename)
{
	ofstream outfile(filename);
	if (outfile.is_open()) {
		outfile << "";
		outfile.flush();
		outfile.close();
	}
	else {
		cerr << "failed: " << errno << std::endl;
	}
}

void Executor::addZeroIfitNeeds(string * str, int n)
{
	if (n < 10)
		str->append("0");
}

string Executor::getCurrentPath()
{
	return currentPath;
}

string Executor::getCurrentDate()
{
	time_t now = time(0);

	tm ltm;
	localtime_s(&ltm, &now);
	string result = "";

	int year = 1900 + ltm.tm_year;
	int month = 1 + ltm.tm_mon;
	int day = ltm.tm_mday;
	int hour = ltm.tm_hour;
	int min = ltm.tm_min;
	int sec = ltm.tm_sec;

	result += to_string(year) + ".";
	addZeroIfitNeeds(&result, month);
	result += to_string(month) + ".";
	addZeroIfitNeeds(&result, day);
	result += to_string(day) + " ";
	addZeroIfitNeeds(&result, hour);
	result += to_string(hour) + ".";
	addZeroIfitNeeds(&result, min);
	result += to_string(min) + ".";
	addZeroIfitNeeds(&result, sec);
	result += to_string(sec);
	return result;
}

vector<vector<int>> Executor::generateAllCombinations(int n, vector<int> numbers)
{
	vector<vector<int>> result;
	int k = n;
	for (int i = 0; i < numbers.size(); i++) {
		if (k >= numbers[i])
		{
			vector<vector<int>> tempResult = generateAllCombinations(k - numbers[i], numbers);
			if (tempResult.size() == 0) {
				vector<int> tmp;
				tmp.push_back(numbers[i]);
				tempResult.push_back(tmp);
			}
			else {
				for (int j = 0; j < tempResult.size(); j++) {
					tempResult[j].push_back(numbers[i]);
				}
			}
			result.insert(result.end(), tempResult.begin(), tempResult.end());
		}
	}
	return result;
}

void Executor::runSearching()
{
	vector<OutResult*> maxAutomats;
	vector<OutResult*> decMaxAutomats;
	int maxSyncWordLength = 0;
	for (int i = 4; i < 64; i++) {
		clearArray(&maxAutomats);
		clearArray(&decMaxAutomats);
		maxSyncWordLength = 0;
		vector<vector<int>> combinations = generateAllCombinations(i, combinationsNumbers);
		for each (vector<int> combination in combinations) {
			Automat * automat = Automat::createAutomat(1, getCurrentPath());
			for (int j = 0; j < combination.size(); j++) {
				Automat * automat2 = Automat::createAutomat(combination[j], getCurrentPath());
				bool isNeedReverse = j % 2;
				if (isNeedReverse)
					automat2->reverse();
				vector<Delta> deltas;
				if (j != 0) {
					deltas.push_back(Delta(automat->states[automat->numberOfStates - 1], automat2->states[0], isNeedReverse));
				}
				deltas.push_back(Delta(automat2->states[0], automat->states[automat->numberOfStates - 1], isNeedReverse));
				automat->concatenateWithOther(automat2, deltas);
				automat2->clear();
			}
			int syncWordLength = automat->generateBooleanAutomat();
			if (maxSyncWordLength < syncWordLength) {
				clearArray(&decMaxAutomats);
				if (maxSyncWordLength == syncWordLength - 1) {
					decMaxAutomats.assign(maxAutomats.begin(), maxAutomats.end());
					maxAutomats.clear();
				}
				else {
					clearArray(&maxAutomats);
				}
				OutResult *result = new OutResult(i + 1, automat->getSyncWord(), syncWordLength, combination);
				maxAutomats.push_back(result);
				maxSyncWordLength = syncWordLength;
			}
			else {
				if (maxSyncWordLength - 1 <= syncWordLength) {
					OutResult *result = new OutResult(i + 1, automat->getSyncWord(), syncWordLength, combination);
					if (maxSyncWordLength == syncWordLength) {
						maxAutomats.push_back(result);
					}
					if (maxSyncWordLength - 1 == syncWordLength) {
						decMaxAutomats.push_back(result);
					}
				}
				else {
					automat->clear();
				}
			}
		}
		printResults(maxAutomats, decMaxAutomats);
	}
}

void Executor::clearArray(vector<OutResult*>* arr)
{
	for (int i = 0; i < arr->size(); i++) {
		delete arr->at(i);
	}
	arr->clear();
}

void Executor::printResults(vector<OutResult*> max, vector<OutResult*> maxDec) {
	for (int i = 0; i < maxDec.size(); i++) {
		maxDec[i]->printToFile(maxDec[i]->makeResult(), offsetFileName);
		maxDec[i]->printResult(maxDec[i]->makeResult());
	}
	for (int i = 0; i < max.size(); i++) {
		max[i]->printToFile(max[i]->makeResult(), maxFileName);
		max[i]->printToFile(max[i]->makeResult(), offsetFileName);
		max[i]->printResult(max[i]->makeResult());
	}
}

void Executor::generateAutomats11744() {
	Automat * automat = Automat::createAutomat(1, getCurrentPath());

	Automat * automat2 = Automat::createAutomat(1, getCurrentPath());
	vector<Delta> deltas;
	deltas.push_back(Delta(automat2->states[0], automat->states[automat->numberOfStates - 1], false));
	automat->concatenateWithOther(automat2, deltas);
	deltas.clear();
	automat2->clear();

	automat2 = Automat::createAutomat(1, getCurrentPath());
	automat2->reverse();
	deltas.push_back(Delta(automat2->states[0], automat->states[automat->numberOfStates - 1], true));
	deltas.push_back(Delta(automat->states[automat->numberOfStates - 1], automat2->states[0], true));
	automat->concatenateWithOther(automat2, deltas);
	deltas.clear();
	automat2->clear();

	automat2 = Automat::createAutomat(7, getCurrentPath());
	deltas.push_back(Delta(automat2->states[0], automat->states[automat->numberOfStates - 1], false));
	deltas.push_back(Delta(automat->states[automat->numberOfStates - 1], automat2->states[0], false));
	automat->concatenateWithOther(automat2, deltas);
	deltas.clear();
	automat2->clear();

	automat2 = Automat::createAutomat(4, getCurrentPath());
	automat2->reverse();
	deltas.push_back(Delta(automat2->states[0], automat->states[automat->numberOfStates - 1], true));
	deltas.push_back(Delta(automat->states[automat->numberOfStates - 1], automat2->states[0], true));
	automat->concatenateWithOther(automat2, deltas);
	deltas.clear();
	automat2->clear();

	automat2 = Automat::createAutomat(4, getCurrentPath());
	deltas.push_back(Delta(automat2->states[0], automat->states[automat->numberOfStates - 1], false));
	deltas.push_back(Delta(automat->states[automat->numberOfStates - 1], automat2->states[0], false));
	automat->concatenateWithOther(automat2, deltas);
	deltas.clear();
	automat2->clear();

	vector<int> combination;
	combination.push_back(1);
	combination.push_back(1);
	combination.push_back(7);
	combination.push_back(4);
	combination.push_back(4);

	string fileName = "combinations117441.txt";
	createFileIfNotExists(fileName);

	for (int i = 18; i < 30; i++) {
		automat2 = Automat::createAutomat(1, getCurrentPath());
		bool isNeedRevers = (i + 1) % 2;
		if (isNeedRevers)
			automat2->reverse();
		deltas.push_back(Delta(automat2->states[0], automat->states[automat->numberOfStates - 1], isNeedRevers));
		deltas.push_back(Delta(automat->states[automat->numberOfStates - 1], automat2->states[0], isNeedRevers));
		automat->concatenateWithOther(automat2, deltas);
		deltas.clear();
		automat2->clear();
		combination.push_back(1);
	}

	for (int i = 30; i < 40; i++) {
		automat2 = Automat::createAutomat(1, getCurrentPath());
		bool isNeedRevers = (i + 1) % 2;
		if (isNeedRevers)
			automat2->reverse();
		deltas.push_back(Delta(automat2->states[0], automat->states[automat->numberOfStates - 1], isNeedRevers));
		deltas.push_back(Delta(automat->states[automat->numberOfStates - 1], automat2->states[0], isNeedRevers));
		automat->concatenateWithOther(automat2, deltas);
		deltas.clear();
		automat2->clear();

		combination.push_back(1);

		int syncWordLength = automat->generateBooleanAutomat();
		float ratio = (float)syncWordLength / (float)(i + 1);
		OutResult *result = new OutResult(i + 1, automat->getSyncWord(), syncWordLength, combination);

		result->printResult(result->makeResult());
		result->printToFile(result->makeResult(), fileName);
	}
}

void Executor::setCombinationsNumbers(vector<int> numbers)
{
	combinationsNumbers.clear();
	combinationsNumbers = numbers;
}

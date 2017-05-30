#include "stdafx.h"
#include "Automat.h"
#include "Executor.h"
#include "Delta.h"
#include "OutResult.h"


Executor::Executor()
{
	maxFileName = Utils::caluclateCurrentDate() + "max" + ".txt";
	offsetFileName = Utils::caluclateCurrentDate() + "offset" + ".txt";
	createFileIfNotExists(maxFileName);
	createFileIfNotExists(offsetFileName);
}

Executor::~Executor()
{
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
			Automat * automat = Automat::createAutomat(combination);
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

	vector<int> combination({ 1, 1, 7, 4, 4 });

	Automat * automat = Automat::createAutomat(combination);

	string fileName = "combinations117441.txt";
	createFileIfNotExists(fileName);

	Automat * automat2;
	vector<Delta> deltas;
	for (int i = 18; i < 30; i++) {
		automat2 = Automat::createAutomat(1);
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
	}

	for (int i = 30; i < 40; i++) {
		automat2 = Automat::createAutomat(1);
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
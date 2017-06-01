#include "stdafx.h"
#include "Automat.h"
#include "Executor.h"
#include "Delta.h"
#include "OutResult.h"


Executor::Executor()
{
	maxFileName = Utils::getCurrentDate() + "max" + ".txt";
	offsetFileName = Utils::getCurrentDate() + "offset" + ".txt";
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

vector<vector<int>> Executor::generateAllCombinations(int sum, vector<int> numbers) {
	sort(numbers.begin(), numbers.end());
	return generateCombinations(sum, numbers);
}

vector<vector<int>> Executor::generateCombinations(int sum, vector<int> numbers)
{
	/*
		Генерирует все комбинации, которыми можно составить sum из numbers,
		т.е. если sum = 5; numbers = [1, 4], то результат будет
		[
			[1, 1, 1, 1, 1],
			[1, 4],
			[4, 1]
		]
	*/
	vector<vector<int>> result;
	int i = 0;
	while (i < numbers.size() && sum >= numbers[i]) {
		// берём всевозможные комбинации для sum - <рассматриваемое число>
		vector<vector<int>> tempResult = generateCombinations(sum - numbers[i], numbers);
		if (tempResult.size() == 0) {
			tempResult.push_back(vector<int>({ numbers[i] }));
		} else {
			appendValueToEveryArray(numbers[i], tempResult);
		}
		result.insert(result.end(), tempResult.begin(), tempResult.end());
		i++;
	}
	return result;
}

void Executor::appendValueToEveryArray(int value, vector<vector<int>> &arrays) {
	for (int j = 0; j < arrays.size(); j++) {
		arrays[j].push_back(value);
	}
}

void Executor::printCombinations(const vector<vector<int>> &combinations) {
	for (int i = 0; i < combinations.size(); i++) {
		for (int j = 0; j < combinations[i].size(); j++) {
			cout << combinations[i][j] << ", ";
		}
		cout << endl;
	}
}

void Executor::runSearching()
{
	vector<OutResult*> maxAutomats;
	vector<OutResult*> decMaxAutomats;
	for (int i = 4; i < 64; i++) {
		maxAutomats.clear();
		decMaxAutomats.clear();
		int maxSyncWordLength = 0;
		vector<vector<int>> combinations = generateAllCombinations(i, combinationsNumbers);
		for each (vector<int> combination in combinations) {
			Automat * automat = new Automat(combination);
			int syncWordLength = automat->generateBooleanAutomat();
			if (maxSyncWordLength < syncWordLength) {
				decMaxAutomats.clear();
				if (maxSyncWordLength == syncWordLength - 1) {
					decMaxAutomats.assign(maxAutomats.begin(), maxAutomats.end());
				}
				maxAutomats.clear();
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

void Executor::findMaxSyncWordForCombination() {

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
	Automat * automat = new Automat(combination);
	string fileName = "combinations117441.txt";
	createFileIfNotExists(fileName);

	cout << "Со скольки состояний начать анализировать? (>=19)" << endl;
	int minN = 0;
	cin >> minN;
	while (minN < 19) {
		cout << "Минимально - 19. Введите число снова." << endl;
		cin >> minN;
	}

	cout << "До скольки состояний анализировать?(>="<< minN << ")" << endl;
	int maxN = 0;
	cin >> maxN;
	while (maxN < minN) {
		cout << "Минимально - " << minN << ". Введите число снова." << endl;
		cin >> maxN;
	}
	minN--;

	Automat * automat2;
	for (int i = automat->numberOfStates; i < minN; i++) {
		bool isNeedRevers = (i + 1) % 2 == 1;
		automat2 = new Automat(1, isNeedRevers);
		automat->concatenateWithOther(automat2, isNeedRevers);
		automat2->clear();
		combination.push_back(1);
	}

	for (int i = minN; i < maxN; i++) {
		bool isNeedRevers = (i + 1) % 2 == 1;
		automat2 = new Automat(1, isNeedRevers);
		automat->concatenateWithOther(automat2, isNeedRevers);

		combination.push_back(1);
		
		/*int syncWordLength = automat->generateBooleanAutomat();
		float ratio = (float)syncWordLength / (float)(i + 1);
		OutResult *result = new OutResult(i + 1, automat->getSyncWord(), syncWordLength, combination);

		result->printResult(result->makeResult());
		result->printToFile(result->makeResult(), fileName);*/
		if (i >= 18 && (i - 18) % 3 == 0) {
			int syncWordLength = automat->generateBooleanAutomat();
			automat->printBooleanAutomatForSyncWord();
		}
	}
}

void Executor::setCombinationsNumbers(vector<int> numbers)
{
	combinationsNumbers.clear();
	combinationsNumbers = numbers;
}
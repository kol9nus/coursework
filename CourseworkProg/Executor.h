#pragma once

class Automat;
class OutResult;

using namespace std;
class Executor
{
public:
	Executor();
	~Executor();

	/**
		Генерирует все комбинации, которыми можно составить sum из numbers.
	*/
	vector<vector<int>> generateAllCombinations(int sum, vector<int> numbers);
	void runSearching();
	void findMaxSyncWordForCombination();
	void generateAutomats11744();
	void setCombinationsNumbers(vector<int>);

private:
	vector<vector<int>> Executor::generateCombinations(int sum, vector<int> numbers);
	void appendValueToEveryArray(int value, vector<vector<int>> &arrays);
	void printCombinations(const vector<vector<int>>& combinations);
	void printResults(vector<OutResult*> max, vector<OutResult*> maxDec);
	void createFileIfNotExists(string filename);
public:

private:
	string maxFileName;
	string offsetFileName;
	vector<int> combinationsNumbers;
	OutResult *maxResult;
};


#pragma once

class Automat;
class OutResult;

using namespace std;
class Executor
{
public:
	Executor();
	~Executor();
	vector<vector<int>> generateAllCombinations(int n, vector<int> numbers);
	void runSearching();
	void generateAutomats11744();
	void setCombinationsNumbers(vector<int>);

private:
	string maxFileName;
	string offsetFileName;
	void clearArray(vector<OutResult*>* arr);
	void printResults(vector<OutResult*> max, vector<OutResult*> maxDec);
	void createFileIfNotExists(string filename);
	void addZeroIfitNeeds(string * str, int n);
public:

private:
	vector<int> combinationsNumbers;
	OutResult *maxResult;
};


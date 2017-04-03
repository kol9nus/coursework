#pragma once

#include <vector>
#include <direct.h>

class Automat;
class OutResult;

using namespace std;
class Executor
{
public:
	Executor();
	~Executor();
	vector<vector<int>> generateAllCombinations(int n, vector<int> numbers);
	string getCurrentPath();
	string getCurrentDate();
	void runSearching();
	void generateAutomats11744();
	void setCombinationsNumbers(vector<int>);

private:
	string defineCurrentPath();
	string maxFileName;
	string offsetFileName;
	void clearArray(vector<OutResult*>* arr);
	void printResults(vector<OutResult*> max, vector<OutResult*> maxDec);
	void createFileIfNotExists(string filename);
	void addZeroIfitNeeds(string * str, int n);
public:

private:
	string currentPath;
	vector<int> combinationsNumbers;
	OutResult *maxResult;
};


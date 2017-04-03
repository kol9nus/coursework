#pragma once
#include <vector>

using namespace std;
class OutResult
{
public:
	OutResult(int numberOfStates, string syncWord, int syncWordLength, vector<int> combination);
	~OutResult();

	string makeResult();
	void printResult(string out);
	void printToFile(string str, string filepath);
	float getOffsetRatio(int offset);
private:
public:
	int numberOfStates;
	string syncWord;
	int syncWordLength;
	vector<int> combination;
	float ratio;
private:

};


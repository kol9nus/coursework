#include "stdafx.h"
#include "OutResult.h"

OutResult::OutResult(int numberOfStates, string syncWord, int syncWordLength, vector<int> combination)
{
	this->numberOfStates = numberOfStates;
	this->syncWord = syncWord;
	this->syncWordLength = syncWordLength;
	this->combination = combination;
	this->ratio = (float)syncWordLength / (float)numberOfStates;
}


OutResult::~OutResult()
{
}

string OutResult::makeResult()
{
	string result = "-------------------------------------------------------------------------------\n";
	result += "n = " + std::to_string(numberOfStates) + "\n";
	for (int i = 0; i < combination.size(); i++) {
		result += to_string(combination[i]) + " ";
	}
	result += "\n";
	result += syncWord + "\n";
	result += "Syncword length: " + std::to_string(syncWordLength) + "\n";
	return result;
}

void OutResult::printResult(string out)
{
	cout << out;
}

void OutResult::printToFile(string str, string filepath)
{
	ofstream out;
	out.open(filepath, std::ios::app);
	out << str;
	out.close();
}

float OutResult::getOffsetRatio(int offset)
{
	return (float)(syncWordLength - offset) / (float)numberOfStates;
}

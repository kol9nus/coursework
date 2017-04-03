#pragma once
#include <iostream>
#include <fstream>
#include <vector>
class State;
class Delta;


using namespace std;
class Automat
{
	// Функции
public:
	Automat();
	~Automat();

	static Automat * createAutomat(int n, string path);

	bool initWithFile(string pathToFile);
	void concatenateWithOther(Automat * automat, vector<Delta> deltas);
	void addState(State * state, vector<Delta> deltas);
	int generateBooleanAutomat();
	int getInselfPath(int index);
	void reverse();
	void clear();
	Automat * copy(Automat* automat);
	string getSyncWord() { return syncWord; };
private:
	vector<int> splitString(string str);
	vector<int> generateStates(int i);
	// Переменные
public:
	int numberOfStates;
	vector<State*> states;
private:
	string syncWord = "";
};


#pragma once
class State;
class Delta;

typedef unsigned long long ull;

using namespace std;
class Automat
{
	// Функции
public:
	Automat(int n, bool isReversed = false);
	Automat(vector<int> combination);
	Automat(const Automat &other);
	~Automat();

	void concatenateWithOther(Automat * automat, bool isB);
	void pushState(State * state, vector<Delta> deltas);
	int generateBooleanAutomat();
	int getInselfPath(int index);
	void reverse();
	void clear();
	string getSyncWord() { return syncWord; };
private:
	bool initWithFile(string pathToFile, bool isReversed);
	vector<int> splitString(string str);
	vector<int> generateStates(ull i);
	// Переменные
public:
	int numberOfStates = 0;
	vector<State*> states;
private:
	string syncWord = "";
};


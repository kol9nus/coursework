#pragma once
class State;
class Delta;


using namespace std;
class Automat
{
	// Функции
public:
	Automat();
	~Automat();

	static Automat * createAutomat(int n, bool isReversed = false);
	static Automat * createAutomat(vector<int> combination);

	void concatenateWithOther(Automat * automat, vector<Delta> deltas);
	void pushState(State * state, vector<Delta> deltas);
	int generateBooleanAutomat();
	int getInselfPath(int index);
	void reverse();
	void clear();
	Automat * copy(Automat* automat);
	string getSyncWord() { return syncWord; };
private:
	bool initWithFile(string pathToFile, bool isReversed);
	vector<int> splitString(string str);
	vector<int> generateStates(int i);
	// Переменные
public:
	int numberOfStates;
	vector<State*> states;
private:
	string syncWord = "";
};


#include "stdafx.h"
#include "Automat.h"
#include "State.h"
#include "Delta.h"

Automat::Automat()
{
}


Automat::~Automat()
{
}

Automat * Automat::createAutomat(int n, string path)
{
	Automat *automat = new Automat();
	//string fileName = "F:\\Study\\3.2\\Coursework\\CourseworkProg\\Debug\\AutomatBlocks\\";
	string fileName = path;
	fileName += "\\AutomatBlocks\\" + std::to_string(n) + "-block.txt";
	if (!automat->initWithFile(fileName)) {
		cout << "trouble:(";
		system("pause");
	}
	return automat;
}

bool Automat::initWithFile(string pathToFile)
{
	string line;
	ifstream ifs(pathToFile);
	if (ifs.is_open())
	{
		vector<int> temp;
		getline(ifs, line);
		temp = splitString(line);
		this->numberOfStates = temp[0];
		for (int i = 0; i < numberOfStates; i++)
			states.push_back(new State(states.size()));
		for (int i = 0; i < numberOfStates; i++)
		{
			getline(ifs, line);
			temp = splitString(line);
			states[i]->setNext(states[temp[0]], states[temp[1]]);
		}
	}
	else {
		return false;
	}
	return true;
}

void Automat::concatenateWithOther(Automat * automat, vector<Delta> deltas)
{
	for (int i = 0; i < automat->numberOfStates; i++) {
		State * next = automat->states[i];
		next->increasIndexes(this->numberOfStates);
		this->states.push_back(next);
	}
	for each (Delta delta in deltas)
		delta.from->setNext(delta.to, delta.symbol);
	this->numberOfStates = numberOfStates + automat->numberOfStates;
}

void Automat::addState(State * state, vector<Delta> deltas)
{
	state->setIndex(numberOfStates);
	states.push_back(state);
	for each (Delta delta in deltas)
		delta.from->setNext(delta.to, delta.symbol);
	numberOfStates++;
}

int Automat::generateBooleanAutomat()
{
	vector<unsigned long long> statesBFS[2];
	vector<string> statesPaths[2];
	if ((1 << this->numberOfStates) - 1 > UINT64_MAX)
		throw exception("overflow");
	vector<vector<bool>> isNumberWasArrays;
	int maxSize = 1 << 30;
	if (this->numberOfStates > 30) {
		vector<bool> isNumberWas(1 << 30, false);
		for (int i = 0; i < (1 << (this->numberOfStates - 30)); i++) {
			isNumberWasArrays.push_back(isNumberWas);
		}
	}
	else {
		vector<bool> isNumberWas(1 << this->numberOfStates, false);
		isNumberWasArrays.push_back(isNumberWas);
	}
	// хватает только для 64 состояний :( Надо будет решить проблемку.
	statesBFS[0].push_back((1<<this->numberOfStates) - 1);
	statesPaths[0].push_back("");
	vector<bool>* isNumberWas;
	int j = 0;
	bool modJ = j % 2;
	while (statesBFS[modJ].size() != 0) {
		statesBFS[!modJ].clear();
		statesPaths[!modJ].clear();
		for (int i = 0; i < statesBFS[modJ].size(); i++)
		{
			int state = statesBFS[modJ][i];
			if (state == 1)
			{
				syncWord = statesPaths[modJ][i];
				return j;
			}
			int nextStateA = 0;
			int nextStateB = 0;
			for each (int s in generateStates(state)) {
				int nextStateAI = 1<<states[s]->getNext(0)->getIndex();
				int nextStateBI = 1<<states[s]->getNext(1)->getIndex();
				if (!(nextStateAI & nextStateA))
					nextStateA += nextStateAI;
				if (!(nextStateBI & nextStateB))
					nextStateB += nextStateBI;
			}
			isNumberWas = &isNumberWasArrays[nextStateA / maxSize];
			if (!isNumberWas->at(nextStateA % maxSize))
			{
				isNumberWas->at(nextStateA % maxSize) = true;
				statesBFS[!modJ].push_back(nextStateA);
				statesPaths[!modJ].push_back(statesPaths[modJ][i] + "a");
			}
			isNumberWas = &isNumberWasArrays[nextStateB / maxSize];
			if (!isNumberWas->at(nextStateB % maxSize))
			{
				isNumberWas->at(nextStateB % maxSize) = true;
				statesBFS[!modJ].push_back(nextStateB);
				statesPaths[!modJ].push_back(statesPaths[modJ][i] + "b");
			}
		}
		j++;
		modJ = j % 2;
	}
	return -1;
}

int Automat::getInselfPath(int index)
{
	if (states[index]->getNext(false)->getIndex() == index)
		return 0;
	if (states[index]->getNext(true)->getIndex() == index)
		return 1;
	return -1;
}

void Automat::reverse()
{
	for each (State * state in states) {
		state->reverse();
	}
}

void Automat::clear()
{
	this->numberOfStates = 0;
	states.clear();
}

Automat * Automat::copy(Automat* automat)
{
	Automat newAutomat;
	newAutomat.numberOfStates = automat->numberOfStates;
	for (int i = 0; i < automat->numberOfStates; i++) {
		newAutomat.states.push_back(new State(automat->states[0]->getIndex()));
	}
	for (int i = 0; i < automat->numberOfStates; i++) {
		State * temp = automat->states[i];
		newAutomat.states[i]->setNext(newAutomat.states[temp->getNext(false)->getIndex()], newAutomat.states[temp->getNext(true)->getIndex()]);
	}
	return &newAutomat;
}

vector<int> Automat::splitString(string str)
{
	vector<int> x;
	int pos = str.find(" ");
	while (pos != string::npos) {
		x.push_back(stoi(str.substr(0, pos)));
		str = str.substr(pos + 1);
		pos = str.find(" ");
	}
	x.push_back(stoi(str));
	return x;
}

vector<int> Automat::generateStates(int i)
{
	vector<int> result;
	int s = 0;
	while (i > 0)
	{
		if (i & 1) {
			result.push_back(s);
		}
		i >>= 1;
		s++;
	}
	return result;
}

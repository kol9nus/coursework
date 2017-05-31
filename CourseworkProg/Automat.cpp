#include "stdafx.h"
#include "Automat.h"
#include "State.h"
#include "Delta.h"

Automat::Automat(int n, bool isReversed)
{
	string fileName = Utils::getLocalPath() + "\\AutomatBlocks\\" + std::to_string(n) + "-block.txt";
	if (!this->initWithFile(fileName, isReversed)) {
		cout << "Не смог инициализировать файлом";
		system("pause");
	}
}

Automat::Automat(vector<int> combination)
	: Automat(1)
{
	for (int j = 0; j < combination.size(); j++) {
		bool isNeedReverse = j % 2 == 1;
		Automat * automat2 = new Automat(combination[j], isNeedReverse);
		this->concatenateWithOther(automat2, isNeedReverse);
		automat2->clear();
	}
}

Automat::Automat(const Automat & other)
{
	this->numberOfStates = other.numberOfStates;
	for (int i = 0; i < other.numberOfStates; i++) {
		this->states.push_back(new State(other.states[0]->getIndex()));
	}
	for (int i = 0; i < other.numberOfStates; i++) {
		State * temp = other.states[i];
		this->states[i]->setNext(
			this->states[temp->getNext(false)->getIndex()],
			this->states[temp->getNext(true)->getIndex()]
		);
	}
}

Automat::~Automat()
{
}

bool Automat::initWithFile(string pathToFile, bool isReversed)
{
	ifstream ifs(pathToFile);
	if (!ifs.is_open())
	{
		return false;
	}

	string line;
	getline(ifs, line);
	vector<int> splittedString = splitString(line);

	this->numberOfStates = splittedString[0];
	for (int i = 0; i < numberOfStates; i++) {
		states.push_back(new State(states.size()));
	}

	for (int i = 0; i < numberOfStates; i++)
	{
		getline(ifs, line);
		splittedString = splitString(line);
		states[i]->setNext(states[splittedString[0]], states[splittedString[1]], isReversed);
	}
	return true;
}

vector<int> Automat::splitString(string str)
{
	stringstream iss(str);
	int number;
	std::vector<int> result;
	while (iss >> number)
		result.push_back(number);
	return result;
}

void Automat::concatenateWithOther(Automat * automat, bool isB)
{
	if (automat->numberOfStates > 0) {
		for each (State *state in automat->states) {
			state->increaseIndex(this->numberOfStates);
			this->states.push_back(state);
		}

		// 0ое состояние должно по обеим стрелкам указывать в себя
		if (this->numberOfStates > 1) {
			states[numberOfStates - 1]->setNext(states[numberOfStates], isB);
		}
		states[numberOfStates]->setNext(states[numberOfStates - 1], isB);

		this->numberOfStates += automat->numberOfStates;

		automat->clear();
	}
}

void Automat::pushState(State * state, vector<Delta> deltas)
{
	state->setIndex(numberOfStates);
	states.push_back(state);
	for each (Delta delta in deltas)
		delta.from->setNext(delta.to, delta.symbol);
	numberOfStates++;
}

int Automat::generateBooleanAutomat()
{
	if ((1 << this->numberOfStates) - 1 > UINT64_MAX || (1 << this->numberOfStates) - 1 > vector<bool>().max_size())
		throw exception("Unreal to calculate on this device");

	ull one = 1;
	vector<bool> isNumberWas(one << this->numberOfStates, false);

	struct BFSState {
		unsigned long long state;
		string path;
	};

	vector<BFSState> statesBFS[2];
	statesBFS[0].push_back({ (one << this->numberOfStates) - 1, "" });

	int j = 0;
	bool modJ = j % 2 == 1;
	while (statesBFS[modJ].size() != 0) {
		statesBFS[!modJ].clear();
		for (int i = 0; i < statesBFS[modJ].size(); i++)
		{
			ull state = statesBFS[modJ][i].state;
			if (state == 1)
			{
				syncWord = statesBFS[modJ][i].path;
				return j;
			}

			ull nextStateA = 0;
			ull nextStateB = 0;
			for each (int s in generateStates(state)) {
				ull nextStateAI = one<<states[s]->getNext(false)->getIndex();
				ull nextStateBI = one<<states[s]->getNext(true)->getIndex();
				if (!(nextStateAI & nextStateA))
					nextStateA += nextStateAI;
				if (!(nextStateBI & nextStateB))
					nextStateB += nextStateBI;
			}
			if (!isNumberWas[nextStateA])
			{
				isNumberWas[nextStateA] = true;
				statesBFS[!modJ].push_back({ nextStateA, statesBFS[modJ][i].path + "a" });
			}
			if (!isNumberWas[nextStateB])
			{
				isNumberWas[nextStateB] = true;
				statesBFS[!modJ].push_back({ nextStateB, statesBFS[modJ][i].path + "b" });
			}
		}
		j++;
		modJ = j % 2 == 1;
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

vector<int> Automat::generateStates(ull i)
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

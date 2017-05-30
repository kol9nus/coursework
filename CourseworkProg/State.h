#pragma once
class State
{
	// Функции
public:
	State(int index);
	State(int index, State** next);
	~State();
	State* getNext(bool num);
	int getIndex();
	void setNext(State* next, bool num);
	void setNext(State* nextA, State* nextB, bool isReversed = false);
	void setIndex(int index);
	void reverse();
	void increasIndex(int value);
private:
	//Переменные
public:
private:
	int index;
	State* next[2];
};


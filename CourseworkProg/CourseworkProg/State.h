#pragma once
class State
{
	// �������
public:
	State(size_t index);
	State(size_t index, State** next);
	~State();
	State* getNext(bool num);
	size_t getIndex();
	void setNext(State* next, bool num);
	void setNext(State* nextA, State* nextB, bool isReversed = false);
	void setIndex(size_t index);
	void reverse();
	void increaseIndex(size_t value);
private:
	//����������
public:
private:
	size_t index;
	State* next[2];
};


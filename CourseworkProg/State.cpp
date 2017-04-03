#include "stdafx.h"
#include "State.h"


State::State(int index)
{
	this->index = index;
}

State::State(int index, State** next)
{
	this->index = index;
	this->next[0] = next[0];
	this->next[1] = next[1];
}


State::~State()
{
}

State * State::getNext(bool num)
{
	return this->next[num];
}

int State::getIndex()
{
	return this->index;
}

void State::setNext(State * next, bool num)
{
	this->next[num] = next;
}

void State::setNext(State * nextA, State * nextB)
{
	this->next[0] = nextA;
	this->next[1] = nextB;
}

void State::setIndex(int index)
{
	this->index = index;
}

void State::reverse()
{
	State * temp = next[1];
	next[1] = next[0];
	next[0] = temp;
}

void State::increasIndexes(int value)
{
	index += value;
}

#include "stdafx.h"
#include "State.h"


State::State(size_t index)
{
	this->index = index;
}

State::State(size_t index, State** next)
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

size_t State::getIndex()
{
	return this->index;
}

void State::setNext(State * next, bool num)
{
	this->next[num] = next;
}

void State::setNext(State * nextA, State * nextB, bool isReversed)
{
	this->next[isReversed] = nextA;
	this->next[!isReversed] = nextB;
}

void State::setIndex(size_t index)
{
	this->index = index;
}

void State::reverse()
{
	State * temp = next[1];
	next[1] = next[0];
	next[0] = temp;
}

void State::increaseIndex(size_t value)
{
	index += value;
}

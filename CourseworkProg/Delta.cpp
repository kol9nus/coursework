#include "stdafx.h"
#include "Delta.h"


Delta::Delta(State * from, State * to, bool symbol)
{
	this->from = from;
	this->to = to;
	this->symbol = symbol;
}

Delta::~Delta()
{
}

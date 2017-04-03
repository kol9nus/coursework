#pragma once
class State;

class Delta
{
public:
	Delta(State* from, State* to, bool symbol);
	~Delta();
private:
public:
	State* from;
	State* to;
	bool symbol;
private:
};


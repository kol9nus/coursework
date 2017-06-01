#include "stdafx.h"
//#include "Executor.h"
#include "Utils.h"
#include "Automat.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	Utils::Init();/*
	Executor executor;
	vector<int> numbers = {1, 4, 7, 10};
	executor.setCombinationsNumbers(numbers);
	executor.generateAutomats11744();*/
	vector<int> combination{ 1, 1, 7, 4, 4 };
	for (int i = 18; i < 34; i++) {
		combination.push_back(1);
	}
	Automat automat(combination);
	automat.printBooleanAutomatForSyncWord("ababaaababaabbabaabbababaabbababaabbababbabbabbbababbaababbabbabababbaababbabbabababbaababbabbabababbaababbabbababaababbaabababbaababaaababbaabababa");
	system("pause");
    return 0;
}

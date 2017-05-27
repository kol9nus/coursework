#include "stdafx.h"
#include "Executor.h"
#include "Utils.h"

int main()
{
	Utils::Init();
	Executor executor;
	vector<int> numbers = {1, 4, 7, 10};
	executor.setCombinationsNumbers(numbers);
	executor.generateAutomats11744();
	system("pause");
    return 0;
}

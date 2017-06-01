#include "stdafx.h"

string Utils::currentDate = "";
string Utils::path = "";

Utils::Utils()
{
}

Utils::~Utils()
{
}

void Utils::Init()
{
	calculatePath();
	caluclateCurrentDate();
}

const string &Utils::getLocalPath()
{
	return path;
}

const string& Utils::getCurrentDate()
{
	return currentDate;
}

void Utils::calculatePath()
{
	char* buffer;
	if ((buffer = _getcwd(NULL, 0)) == NULL)
		perror("_getcwd error");
	path = string(buffer);
}

void Utils::caluclateCurrentDate()
{
	time_t now = time(0);

	tm ltm;
	localtime_s(&ltm, &now);
	string result = "";

	int year = 1900 + ltm.tm_year;
	int month = 1 + ltm.tm_mon;
	int day = ltm.tm_mday;
	int hour = ltm.tm_hour;
	int min = ltm.tm_min;
	int sec = ltm.tm_sec;

	result += to_string(year) + ".";
	addZeroIfitNeeds(&result, month);
	result += to_string(month) + ".";
	addZeroIfitNeeds(&result, day);
	result += to_string(day) + " ";
	addZeroIfitNeeds(&result, hour);
	result += to_string(hour) + ".";
	addZeroIfitNeeds(&result, min);
	result += to_string(min) + ".";
	addZeroIfitNeeds(&result, sec);
	result += to_string(sec);

	currentDate = result;
}

void Utils::addZeroIfitNeeds(string * str, int n)
{
	if (n < 10)
		str->append("0");
}

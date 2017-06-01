#pragma once
using namespace std;
class Utils
{
public:
	Utils();
	~Utils();
	static void Init();
	static const string &getLocalPath();
	static const string &getCurrentDate();

	static void calculatePath();
	static void caluclateCurrentDate();

private:
	static void addZeroIfitNeeds(string* str, int n);

	static string currentDate;
	static string path; // Путь до исполнияемого файла
};


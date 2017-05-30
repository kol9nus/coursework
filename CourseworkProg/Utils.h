#pragma once
class Utils
{
public:
	Utils();
	~Utils();
	static void Init();
	const std::string &getLocalPath();
	const std::string &getCurrentDate();

	static Utils utils;
	static std::string calculatePath();
	static std::string caluclateCurrentDate();

private:
	static void addZeroIfitNeeds(std::string* str, int n);

	std::string currentDate;
	std::string path; // Путь до исполнияемого файла
};


#pragma once
class Utils
{
public:
	Utils();
	~Utils();
	static void Init();
	static const std::string &getLocalPath();
	static const std::string &getCurrentDate();

private:
	static void calculatePath();
	static std::string caluclateCurrentDate();
	static void addZeroIfitNeeds(std::string* str, int n);

	static std::string currentDate;
	static std::string path; // Путь до исполнияемого файла
};


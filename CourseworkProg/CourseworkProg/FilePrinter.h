#pragma once

using namespace std;
class FilePrinter
{
public:
	FilePrinter(string filename);
	~FilePrinter();

	void operator()(string line);
private:
	void createOrTruncFile(string filename);
	bool isUserWantsToCreateFile(string filename);

	ofstream out;
	string filePath;
};


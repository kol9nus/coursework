#include "stdafx.h"
#include "FilePrinter.h"


FilePrinter::FilePrinter(string filename)
{
	createOrTruncFile(filename);
	filePath = filename;
}

void FilePrinter::createOrTruncFile(string filename)
{
	bool createFile = isUserWantsToCreateFile(filename);

	if (!createFile) {
		throw new exception(("Файл " + filename + " уже существует.").c_str());
	}

	out.open(filename);
	if (!out.is_open()) {
		throw new exception(("Неудалось открыть файл " + filename + " на запись.").c_str());
	}
	out << "";
	out.flush();
	out.close();
}

bool FilePrinter::isUserWantsToCreateFile(string filename) {
	char answer = 'y';
	if (ifstream(filename))
	{
		cout << "Файл " << filename << " уже существует. Хотите пересоздать его? (y/n)" << endl;
		cin >> answer;
		while (answer != 'y' && answer != 'n') {
			cout << "Неправильный ввод. Введите y или n";
			cin >> answer;
		}
	}
	return answer == 'y';
}

void FilePrinter::operator()(string line)
{
	out.open(filePath, std::ios::app);
	out << line;
	out.close();
}


FilePrinter::~FilePrinter()
{
}

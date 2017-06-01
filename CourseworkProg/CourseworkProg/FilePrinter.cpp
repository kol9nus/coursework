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
		throw new exception(("���� " + filename + " ��� ����������.").c_str());
	}

	out.open(filename);
	if (!out.is_open()) {
		throw new exception(("��������� ������� ���� " + filename + " �� ������.").c_str());
	}
	out << "";
	out.flush();
	out.close();
}

bool FilePrinter::isUserWantsToCreateFile(string filename) {
	char answer = 'y';
	if (ifstream(filename))
	{
		cout << "���� " << filename << " ��� ����������. ������ ����������� ���? (y/n)" << endl;
		cin >> answer;
		while (answer != 'y' && answer != 'n') {
			cout << "������������ ����. ������� y ��� n";
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

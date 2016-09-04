#include "stdafx.h"

static const std::string fileName = "file/surname.txt";

struct Surname
{
	int startBytes;
	int amountChar;
	std::string word;
};

void SaveData(std::string &const word, int &const position, std::vector<Surname>& surname)
{
	Surname structSurname;
	structSurname.word = word;
	structSurname.startBytes = position;
	structSurname.amountChar = word.length();
	surname.push_back(structSurname);
	std::cout << structSurname.startBytes << std::endl;
}

void PushInVector()
{
}
void ReadSurname(FILE* &const file, std::vector<Surname>& surname)
{
	char ch;
	std::string word;

	fpos_t pointerPositionInFile;
	while ((ch = getc(file)) != EOF)
	{
		std::cout << ch;
		if (ch == '\n')
		{
			if (word != "")
			{
				fgetpos(file, &pointerPositionInFile);
				int position = pointerPositionInFile - word.length() - 2;
				SaveData(word, position, surname);
				word = "";
			}
		}
		else
		{
			word += ch;
		}
	}
	if (word != "")
	{
		fgetpos(file, &pointerPositionInFile);
		int position = pointerPositionInFile - word.length();
		SaveData(word, position, surname);
		word = "";
	}
}

bool CompareStrings(std::string &const a, std::string &const b)
{
	return (strcmp(a.c_str(), b.c_str())) > 0;
}

Surname SearchSurname(std::vector<Surname> &const surname)
{
	Surname maxSurname;
	maxSurname = surname[0];
	if (surname.size() >= 2)
	{
		for (int i = 1; i != surname.size(); i++)
		{
			if (CompareStrings(maxSurname.word, surname[i].word))
			{
				maxSurname = surname[i];
			}
		}
	}
	return maxSurname;
}

void ReplaceWord(FILE* & file, Surname &const surname)
{
	std::string buf;
	for (int i = 0; i != surname.amountChar; i++)
	{
		buf += "*";
	}
	fseek(file, surname.startBytes, SEEK_SET);
	fwrite(buf.c_str(), surname.amountChar, 1, file);
}

FILE* OpenFile()
{
	FILE* file;
    fopen_s(&file, fileName.c_str(), "r+");
	return file;
}

int main()
{
	//setlocale(LC_ALL, "Russian");
	FILE* fileWithSurname = OpenFile();
	if (fileWithSurname && (sizeof(fileWithSurname) != 0))
	{
		std::vector<Surname> surname;
		ReadSurname(fileWithSurname, surname);
		if (surname.size() != 0)
		{
			Surname maxSurname = SearchSurname(surname);
			ReplaceWord(fileWithSurname, maxSurname);
		}
	}
	else
	{
		std::cout << "Something wrong with the file!!!" << std::endl;
	}
	fclose(fileWithSurname);
	system("pause");
	return 1;
}

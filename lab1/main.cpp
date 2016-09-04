#include "stdafx.h"

static const std::string fileName = "file/surname.txt";
static const char REPLACEMENT = '*';

struct Surname
{
	int startBytes;
	int amountChar;
	std::string word;
};

void AddToVector(std::string const& word, int const& position, std::vector<Surname>& surname)
{
	Surname structSurname;
	structSurname.word = word;
	structSurname.startBytes = position;
	structSurname.amountChar = word.length();
	surname.push_back(structSurname);
}
 
void SaveData(std::string &word, std::vector<Surname>& surname, fpos_t const& pointerPositionInFile)
{
	if (word != "")
	{
		int position = static_cast<int>(pointerPositionInFile) - word.length();
		AddToVector(word, position, surname);
		word = "";
	}
}
void ReadSurname(FILE* const& file, std::vector<Surname>& surname)
{
	char ch;
	std::string word;

	fpos_t pointerPositionInFile;
	while ((ch = getc(file)) != EOF)
	{
		if (ch == '\n')
		{
			fgetpos(file, &pointerPositionInFile);
			SaveData(word, surname, pointerPositionInFile-2);
		}
		else
		{
			word += ch;
		}
	}
	fgetpos(file, &pointerPositionInFile);
	SaveData(word, surname, pointerPositionInFile);
}

int CompareStrings(std::string const& a, std::string const& b)
{
	return (strcmp(a.c_str(), b.c_str()));
}

std::string GetStringReplacement(Surname const& surname)
{
	std::string buf = "";
	for (int i = 0; i != surname.amountChar; i++)
	{
		buf += REPLACEMENT;
	}
	return buf;
}
bool IsReplaced(Surname const& surname)
{
	bool isReplaced = true;
	std::string replacement = GetStringReplacement(surname);
	if (CompareStrings(surname.word, replacement) == 0)
	{
		isReplaced = false;
	}
	return isReplaced;
}

Surname SearchSurname(std::vector<Surname> const& surname)
{
	Surname maxSurname;
	maxSurname = surname[0];
	if (surname.size() >= 2)
	{
		for (int i = 1; i != surname.size(); i++)
		{
			if ((CompareStrings(maxSurname.word, surname[i].word) > 0) /*&& IsReplaced(surname[i])*/)
			{
				maxSurname = surname[i];
			}
		}
	}
	return maxSurname;
}

void ReplaceWord(FILE* & file, Surname const& surname)
{
	std::string replacement = GetStringReplacement(surname);
	fseek(file, surname.startBytes, SEEK_SET);
	fwrite(replacement.c_str(), surname.amountChar, 1, file);
}

FILE* OpenFile()
{
	FILE* file;
    fopen_s(&file, fileName.c_str(), "r+");
	return file;
}

int main()
{
	setlocale(LC_ALL, "Russian");
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
	//system("pause");
	return 1;
}

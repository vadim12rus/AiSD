#include <stdio.h> 
#include <iostream>
#include <vector>
#include <cstring>

struct Surname
{
	int startBytes; //Порядковый номер
	int amountChar;
	std::string word;
};

void ReadSurname(FILE* &const file, std::vector<Surname>& surname)
{
	char ch;
	std::string word;

	fpos_t position;
	while ((ch = getc(file)) != EOF)
	{
		if (ch == '\n')
		{
			fgetpos(file, &position);
			Surname structSurname;
			structSurname.word = word;
			structSurname.startBytes = position - word.length() - 2;
			structSurname.amountChar = word.length();
			surname.push_back(structSurname);
			word = "";
		}
		else
		{
			word += ch;
		}
	}
}

bool sur(std::string &const c, std::string &const d)
{
	std::string a = c, b = d;
	return strcmp(a.c_str(), b.c_str());
}

Surname SearchSurname(std::vector<Surname> &const surname)
{
	Surname maxSurname;
	maxSurname.word = surname[0].word;
	for (int i = 1; i != surname.size(); i++)
	{
		if ((strcmp(maxSurname.word.c_str(), surname[i].word.c_str())) > 0)
		{
			std::cout << surname[i].word.c_str() << std::endl;
			maxSurname = surname[i];
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
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	FILE* fileWithSurname;
	fopen_s(&fileWithSurname, "surname.txt", "r+");
	if (fileWithSurname && (sizeof(fileWithSurname) != 0))
	{
		vector<Surname> surname;
		ReadSurname(fileWithSurname, surname);
		Surname maxSurname = SearchSurname(surname);
		ReplaceWord(fileWithSurname, maxSurname);
	}
	else
	{
		cout << "Something wrong with the file!!!" << endl;
	}
	fclose(fileWithSurname);
	system("pause");
	return 0;
}

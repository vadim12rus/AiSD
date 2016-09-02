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
			structSurname.startBytes = position;
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

Surname SearchSurname(std::vector<Surname> &const surname)
{
	Surname maxSurname;
	maxSurname.word = "";
	if (strcmp("hg", "fg") > 0)
	{
		std::cout << "vadim"<< std::endl;
	}
	for (int i = 0; i != surname.size(); i++)
	{
		if (strcmp(surname[i].word, maxSurname.word)) > 0)
		{
			maxSurname = surname[i];
		}
	}
	std::cout << maxSurname.amountChar << std::endl;
	return maxSurname;
}

using namespace std;

int main()
{
	FILE* fileWithSurname;
	fopen_s(&fileWithSurname, "surname.txt", "r+");
	if (fileWithSurname && (sizeof(fileWithSurname) != 0))
	{
		vector<Surname> surname;
		ReadSurname(fileWithSurname, surname);
		SearchSurname(surname);
		//char* buf = "0123456";
		//fseek(fileWithSurname, 11, SEEK_SET);
		//fwrite(buf, 7, 1, fileWithSurname);
	}
	else
	{
		cout << "Something wrong with the file!!!" << endl;
	}
	fclose(fileWithSurname);
	system("pause");
	return 0;
}

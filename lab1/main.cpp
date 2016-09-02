#include <stdio.h> 
#include <iostream>

struct Surname
{
	int startBytes;
	int amountBytes;
	std::string word;
};

using namespace std;

int main()
{
	FILE* f;
	fopen_s(&f, "surname.txt", "r+");
	if (f)
	{
		char* buf = "0123456";
		fseek(f, 11, SEEK_SET);
		fwrite(buf, 7, 1, f);
		fclose(f);
	}
	system("pause");
	return 0;
}
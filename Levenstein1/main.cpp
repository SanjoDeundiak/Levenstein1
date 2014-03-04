#include "Levenstein.h"
#include <fstream>
#include <string>

using std::wstring;
using std::endl;

int main()
{
	char *a = setlocale(LC_ALL, "ru-Ru");
	std::locale loc("ru-Ru");

	std::wifstream wcin("input.txt");
	std::wofstream wcout("output.txt");

	wcin.imbue(loc);
	wcout.imbue(loc);

	wstring st1, st2;
	std::getline(wcin, st1);
	std::getline(wcin, st2);

	wcout << st1 << endl << st2 << endl;

	Levenstein lev(st1, st2); 		
	
	wcout << lev.L();		
}
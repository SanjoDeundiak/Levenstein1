#include "Levenstein.h"
#include <vector>
#include <algorithm>

using std::vector;
using std::pair;

const int replace = 5;
const int reg = 1;
const int sim = 3;

map<wchar_t, wchar_t> Levenstein::similar = std::map<wchar_t, wchar_t>
{
	pair<wchar_t, wchar_t>(L'Á', L'Ï'),
	pair<wchar_t, wchar_t>(L'Ò', L'Ä'),
	pair<wchar_t, wchar_t>(L'Ê', L'Ã'),
	pair<wchar_t, wchar_t>(L'Ñ', L'Ç'),
	pair<wchar_t, wchar_t>(L'È', L'Û'),
	pair<wchar_t, wchar_t>(L'²', L'¯'),
	pair<wchar_t, wchar_t>(L'Å', L'İ'),
	pair<wchar_t, wchar_t>(L'¨', L'Å'),
	pair<wchar_t, wchar_t>(L'À', L'Î'),
	pair<wchar_t, wchar_t>(L'ß', L'À'),
	pair<wchar_t, wchar_t>(L'Î', L'¨'),
	pair<wchar_t, wchar_t>(L'Ó', L'Ş'),	
	pair<wchar_t, wchar_t>(L'P', L'B'),
	pair<wchar_t, wchar_t>(L'T', L'D'),
	pair<wchar_t, wchar_t>(L'K', L'G'),
	pair<wchar_t, wchar_t>(L'F', L'V'),
	pair<wchar_t, wchar_t>(L'S', L'Z'),
	pair<wchar_t, wchar_t>(L'C', L'G'),	
};

Levenstein::Levenstein(const wstring &s1, const wstring &s2) :
	st1(s1), st2(s2)	
{
	if (st2.length() < st1.length())
		std::swap(st1, st2);
	l = 1 - (double(calculate()) / st2.length()) / replace;
}

double Levenstein::L() const
{
	return l;
}

int Levenstein::cost(wchar_t a, wchar_t b) const
{
	wchar_t au, bu;
	au = towupper(a); bu = towupper(b);
	bool r1 = (au == a), r2 = (bu == b);
	
	if (a == b)
		return 0;
	else if (au == bu)
		return reg;
	int cst = replace;

	if ((similar.count(au) && similar[au] == bu) || (similar.count(bu) && similar[bu] == au))
		cst = sim + ((r1 == r2) ? 0 : reg);	
	
	return cst;
}

int Levenstein::calculate() const
{
	if (st1 == st2)
		return 0;	
	size_t len1 = st1.length(), len2 = st2.length();
	if (!len1)
		return len2;
	if (!len2)
		return len1;

	vector<int> v1(len1 + 1), v2(len1 + 1);

	for (size_t i = 0; i <= len1; i++)
		v1[i] = i * replace;

	for (size_t i = 1; i <= len2; i++)
	{
		v2[0] = i * replace;
		for (size_t j = 1; j <= len1; j++)								
			v2[j] = std::min( { v1[j] + replace, v2[j - 1] + replace, v1[j - 1] + cost(st1[j - 1], st2[i - 1]) } );					
		v1 = v2;
	}
	return v2[len1];
}

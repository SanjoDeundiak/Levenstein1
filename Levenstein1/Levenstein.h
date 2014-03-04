#pragma once

#include <string>
#include <map>

using std::wstring;
using std::map;

class Levenstein
{
	wstring st1;
	wstring st2;
	double l;
	static map<wchar_t, wchar_t> similar;
	int cost(wchar_t c1, wchar_t c2) const;
	int calculate() const;
public:
	double L() const;
	Levenstein(const wstring &s1, const wstring &s2);
};
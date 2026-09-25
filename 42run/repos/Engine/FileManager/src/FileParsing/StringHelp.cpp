#include "FileParsing/StringHelp.hpp"



StringHelp::CharPallet::CharPallet(const char * pallet)
{
	Pallet = pallet;
	Count = 0;
	while (Pallet[Count] != '\0') { Count++; }
}

bool StringHelp::CharPallet::Check(const char & c) const
{
	for (unsigned int i = 0; i < Count; i++)
	{
		if (Pallet[i] == c) { return true; }
	}
	return false;
}





size_t StringHelp::FindNextAny(const std::string & str, size_t idx, const CharPallet & pallet)
{
	while (idx < str.length())
	{
		const char & c = str[idx];
		if (pallet.Check(c))
		{
			return idx;
		}
		idx++;
	}
	return std::string::npos;
}

std::string StringHelp::RemoveFromString(const std::string & str, const CharPallet & pallet)
{
	std::string s = "";

	size_t idx0 = 0;
	size_t idx1 = FindNextAny(str, idx0, pallet);
	while (idx1 != std::string::npos)
	{
		s += CutInEx(str, idx0, idx1);
		idx0 = idx1 + 1;
		idx1 = FindNextAny(str, idx0, pallet);
	}
	s += CutInEx(str, idx0, str.length());

	return s;
}

std::string StringHelp::RemoveFromString(const std::string & str, const CharPallet & pallet0, const CharPallet & pallet1)
{
	std::string s = "";

	size_t idx0 = 0;
	size_t idx1 = FindNextAny(str, idx0, pallet0);
	if (idx1 == std::string::npos)
	{
		s += CutInEx(str, idx0, str.length());
	}
	while (idx1 != std::string::npos)
	{
		s += CutInEx(str, idx0, idx1);
		idx0 = FindNextAny(str, idx1, pallet1);
		if (idx0 == std::string::npos)
		{
			break;
		}
		idx0++;
		idx1 = FindNextAny(str, idx0, pallet0);
		if (idx1 == std::string::npos)
		{
			s += CutInEx(str, idx0, str.length());
			break;
		}
	}

	return s;
}

std::string StringHelp::CutInEx(const std::string & str, size_t idx0, size_t idx1)
{
	return str.substr(idx0, idx1 - idx0);
}

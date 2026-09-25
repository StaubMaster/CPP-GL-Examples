#ifndef  STRING_HELP_HPP
# define STRING_HELP_HPP

#include <string>

namespace StringHelp
{
	struct CharPallet
	{
		unsigned int Count;
		const char * Pallet;

		CharPallet(const char * pallet);

		bool Check(const char & c) const;
	};

	size_t FindNextAny(const std::string & str, size_t idx, const CharPallet & pallet);

	std::string RemoveFromString(const std::string & str, const CharPallet & pallet);
	std::string RemoveFromString(const std::string & str, const CharPallet & pallet0, const CharPallet & pallet1);

	std::string CutInEx(const std::string & str, size_t idx0, size_t idx1);
};


#endif

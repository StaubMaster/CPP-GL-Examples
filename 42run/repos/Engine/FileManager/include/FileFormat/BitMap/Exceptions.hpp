#ifndef  BITMAP_EXCEPTIONS_HPP
# define BITMAP_EXCEPTIONS_HPP

# include "FileParsing/ExceptionBase.hpp"
# include "uint.hpp"

namespace BitMap
{
	namespace Exceptions
	{
		class UnknownSignature : public ExceptionBase
		{
			public:
			UnknownSignature();
		};

		class UnknownHeader : public ExceptionBase
		{
			public:
			UnknownHeader();
		};
		class UnknownHeaderValue : public ExceptionBase
		{
			public:
			UnknownHeaderValue(const char * name, const char * val);
			UnknownHeaderValue(const char * name, uint8 val);
			UnknownHeaderValue(const char * name, uint16 val);
			UnknownHeaderValue(const char * name, uint32 val);
			UnknownHeaderValue(const char * name, uint64 val);
		};
	};
};

#endif
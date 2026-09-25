#include "FileFormat/BitMap/Exceptions.hpp"
#include <sstream>



BitMap::Exceptions::UnknownSignature::UnknownSignature()
	: ExceptionBase()
{
	Text = "BitMap: Unknown Signature.";
}



BitMap::Exceptions::UnknownHeader::UnknownHeader()
	: ExceptionBase()
{
	Text = "BitMap: Unknown Header.";
}



BitMap::Exceptions::UnknownHeaderValue::UnknownHeaderValue(const char * name, const char * val)
	: ExceptionBase()
{
	std::ostringstream ss("BitMap: UnknownHeaderValue: ");
	ss << name << ": " << val << ".";
	Text = ss.str();
}
BitMap::Exceptions::UnknownHeaderValue::UnknownHeaderValue(const char * name, uint8 val)
	: ExceptionBase()
{
	std::ostringstream ss("BitMap: UnknownHeaderValue: ");
	ss << name << ": " << val << ".";
	Text = ss.str();
}
BitMap::Exceptions::UnknownHeaderValue::UnknownHeaderValue(const char * name, uint16 val)
	: ExceptionBase()
{
	std::ostringstream ss("BitMap: UnknownHeaderValue: ");
	ss << name << ": " << val << ".";
	Text = ss.str();
}
BitMap::Exceptions::UnknownHeaderValue::UnknownHeaderValue(const char * name, uint32 val)
	: ExceptionBase()
{
	std::ostringstream ss("BitMap: UnknownHeaderValue: ");
	ss << name << ": " << val << ".";
	Text = ss.str();
}
BitMap::Exceptions::UnknownHeaderValue::UnknownHeaderValue(const char * name, uint64 val)
	: ExceptionBase()
{
	std::ostringstream ss("BitMap: UnknownHeaderValue: ");
	ss << name << ": " << val << ".";
	Text = ss.str();
}

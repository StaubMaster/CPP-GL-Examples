#include "FilePathSegment.hpp"



FilePathSegment::FilePathSegment() :
	Length(0),
	String(0)
{ }
FilePathSegment::~FilePathSegment()
{
	delete[] String;
}

FilePathSegment::FilePathSegment(const FilePathSegment & other) :
	Length(other.Length),
	String(new char[Length + 1])
{
	for (unsigned int i = 0; i < Length; i++)
	{
		String[i] = other.String[i];
	}
	String[Length] = '\0';
}
FilePathSegment & FilePathSegment::operator=(const FilePathSegment & other)
{
	delete[] String;
	Length = other.Length;
	String = new char[Length + 1];
	for (unsigned int i = 0; i < Length; i++)
	{
		String[i] = other.String[i];
	}
	String[Length] = '\0';
	return *this;
}



void FilePathSegment::FromTo(const char * str, unsigned int from, unsigned int to)
{
	delete[] String;
	Length = to - from;
	String = new char[Length + 1];
	for (unsigned int i = 0; i < Length; i++)
	{
		String[i] = str[from + i];
	}
	String[Length] = '\0';
}

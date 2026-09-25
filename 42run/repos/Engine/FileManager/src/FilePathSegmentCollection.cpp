#include "FilePathSegmentCollection.hpp"

#if defined(_WIN32)
# define SLASH '\\'
#endif

#if defined(__APPLE__)
# define SLASH '/'
#endif

#if defined(__linux__)
# define SLASH '/'
#endif

//#include <iostream>





unsigned int FilePathSegmentCollection::Count() const { return _Count; }
FilePathSegment & FilePathSegmentCollection::operator[](unsigned int idx) { return _Segments[idx]; }
const FilePathSegment & FilePathSegmentCollection::operator[](unsigned int idx) const { return _Segments[idx]; }





FilePathSegmentCollection::FilePathSegmentCollection() :
	_Count(0),
	_Segments(0)
{
	//std::cout << "  ++++  FilePathSegmentCollection " << this << " " << _Count << " " << _Segments << "\n";
}
FilePathSegmentCollection::~FilePathSegmentCollection()
{
	//std::cout << "  ----  FilePathSegmentCollection " << this << " " << _Count << " " << _Segments << "\n";
	delete[] _Segments;
}

FilePathSegmentCollection::FilePathSegmentCollection(const FilePathSegmentCollection & other) :
	_Count(other._Count),
	_Segments(new FilePathSegment[_Count])
{
	//std::cout << "  ====  FilePathSegmentCollection " << this << " " << _Count << " " << _Segments << "\n";
	for (unsigned int i = 0; i < _Count; i++)
	{
		_Segments[i] = other._Segments[i];
	}
}
FilePathSegmentCollection & FilePathSegmentCollection::operator=(const FilePathSegmentCollection & other)
{
	//std::cout << "  this  FilePathSegmentCollection " << this << " " << _Count << " " << _Segments << "\n";
	//std::cout << "  other FilePathSegmentCollection " << &other << " " << other._Count << " " << other._Segments << "\n";
	delete[] _Segments;
	_Count = other._Count;
	_Segments = new FilePathSegment[_Count];
	for (unsigned int i = 0; i < _Count; i++)
	{
		_Segments[i] = other._Segments[i];
	}
	//std::cout << "FilePathSegmentCollection = done\n";
	return *this;
}



FilePathSegmentCollection FilePathSegmentCollection::RemoveLast() const
{
	FilePathSegmentCollection collection;
	if (_Count != 0) { collection._Count = _Count - 1; }
	collection._Segments = new FilePathSegment[collection._Count];
	for (unsigned int i = 0; i < collection._Count; i++)
	{
		collection._Segments[i] = _Segments[i];
	}
	//std::cout << "RemoveLast() return " << &collection << " " << collection._Count << " " << collection./_Segments << "\n";
	return collection;
}
FilePathSegmentCollection FilePathSegmentCollection::Append(const FilePathSegmentCollection & other) const
{
	FilePathSegmentCollection collection;
	collection._Count = _Count + other._Count;
	collection._Segments = new FilePathSegment[collection._Count];
	for (unsigned int i = 0; i < _Count; i++)
	{
		collection._Segments[i] = _Segments[i];
	}
	for (unsigned int i = 0; i < other._Count; i++)
	{
		collection._Segments[i + _Count] = other._Segments[i];
	}
	//std::cout << "Append() return " << &collection << " " << collection._Count << " " << collection._Segments << "\n";
	return collection;
}



FilePathSegmentCollection FilePathSegmentCollection::Split(const char * path)
{
	unsigned int len = 0;
	while (path[len] != '\0') { len++; }
	char * str = new char[len + 1];
	for (unsigned int i = 0; i < len; i++)
	{
		if (path[i] == '/' || path[i] == '\\')
		{ str[i] = SLASH; }
		else
		{ str[i] = path[i]; }
	}
	str[len] = '\0';

	FilePathSegmentCollection collection;
	
	//	_Count
	if (len != 0)
	{
		unsigned int i = 0;
		if (str[i] == SLASH)
		{
			for (; i < len; i++)
			{
				if (str[i] != SLASH)
				{
					i++;
					collection._Count++;
					break;
				}
			}
			if (i == len) { collection._Count++; }
		}
		else
		{
			collection._Count++;
		}

		for (; i < len; i++)
		{
			if (str[i] != SLASH && (i != 0 && str[i - 1] == SLASH))
			{
				collection._Count++;
			}
		}
	}

	//	Take
	collection._Segments = new FilePathSegment[collection._Count];
	if (len != 0)
	{
		unsigned int idx = 0;
		unsigned int off;
		unsigned int i = 0;
		if (str[i] == SLASH)
		{
			for (; i < len; i++)
			{
				if (str[i] != SLASH)
				{
					off = i - 1;
					i++;
					break;
				}
			}
			if (i == len)
			{
				collection._Segments[idx].FromTo(str, len - 1, len);
			}
		}
		else
		{
			off = i;
		}

		for (; i < len; i++)
		{
			if (str[i] != SLASH && (i != 0 && str[i - 1] == SLASH))
			{
				off = i;
			}
			if (str[i] == SLASH && (i != 0 && str[i - 1] != SLASH))
			{
				collection._Segments[idx].FromTo(str, off, i);
				idx++;
			}
		}
		if (str[len - 1] != SLASH)
		{
			collection._Segments[idx].FromTo(str, off, len);
			idx++;
		}
	}
	delete[] str;

	//std::cout << "Split() return " << &collection << " " << collection._Count << " " << collection._Segments << "\n";
	return collection;
}



char * FilePathSegmentCollection::ToString() const
{
	unsigned int len = 0;
	for (unsigned int i = 0; i < _Count; i++)
	{
		len += _Segments[i].Length;
	}
	if (_Count != 0) { len += _Count - 1; }

	unsigned int idx = 0;
	char * str = new char[len + 1];
	for (unsigned int i = 0; i < _Count; i++)
	{
		if (i != 0)
		{
			str[idx] = SLASH;
			idx++;
		}
		for (unsigned int j = 0; j < _Segments[i].Length; j++)
		{
			str[idx] = _Segments[i].String[j];
			idx++;
		}
	}
	str[len] = '\0';
	return str;
}





#include <iostream>
std::ostream & operator<<(std::ostream & o, const FilePathSegmentCollection & obj)
{
	char * str = obj.ToString();
	o << ((const char *)str);
	delete[] str;
	return o;
}

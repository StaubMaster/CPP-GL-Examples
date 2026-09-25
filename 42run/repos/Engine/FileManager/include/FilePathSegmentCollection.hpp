#ifndef  FILE_PATH_SEGMENT_COLLECTION_HPP
# define FILE_PATH_SEGMENT_COLLECTION_HPP

# include "FilePathSegment.hpp"

class FilePathSegmentCollection
{
	private:
	unsigned int _Count;
	FilePathSegment * _Segments;
	// Container::Array<>

	public:
	unsigned int Count() const;
	FilePathSegment & operator[](unsigned int idx);
	const FilePathSegment & operator[](unsigned int idx) const;

	//private:
	//void Allocate();

	public:
	FilePathSegmentCollection();
	~FilePathSegmentCollection();

	FilePathSegmentCollection(const FilePathSegmentCollection & other);
	FilePathSegmentCollection & operator=(const FilePathSegmentCollection & other);

	FilePathSegmentCollection RemoveLast() const;
	FilePathSegmentCollection Append(const FilePathSegmentCollection & other) const;

	static FilePathSegmentCollection Split(const char * path);
	// also take std::string

	char * ToString() const;
	// also return std::string
};

# include <iosfwd>
std::ostream & operator<<(std::ostream & o, const FilePathSegmentCollection & obj);

#endif
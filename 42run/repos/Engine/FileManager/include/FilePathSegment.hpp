#ifndef  FILE_PATH_SEGMENT_HPP
# define FILE_PATH_SEGMENT_HPP

struct FilePathSegment
{
	unsigned int Length;
	char * String;

	FilePathSegment();
	~FilePathSegment();

	FilePathSegment(const FilePathSegment & other);
	FilePathSegment & operator=(const FilePathSegment & other);

	void FromTo(const char * str, unsigned int from, unsigned int to);
};

#endif
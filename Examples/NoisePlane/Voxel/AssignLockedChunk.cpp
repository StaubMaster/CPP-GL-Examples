#include "AssignLockedChunk.hpp"
#include "Chunk.hpp"



bool		AssignLockedChunk::Is() const { return (Pointer != nullptr); }
Chunk &		AssignLockedChunk::operator*() { return (*Pointer); }

AssignLockedChunk::~AssignLockedChunk()
{
	if (Count != nullptr)
	{
		if ((*Count) == 0)
		{
			delete Count;
			if (Pointer != nullptr)
			{
				Pointer -> AssignU();
			}
		}
		else
		{
			(*Count)--;
		}
	}
}
AssignLockedChunk::AssignLockedChunk()
	: Count(nullptr)
	, Pointer(nullptr)
{ }
AssignLockedChunk::AssignLockedChunk(const AssignLockedChunk & other)
	: Count(other.Count)
	, Pointer(other.Pointer)
{
	if (Count != nullptr)
	{
		(*Count)++;
	}
}
AssignLockedChunk & AssignLockedChunk::operator=(const AssignLockedChunk & other)
{
	if (Count != nullptr)
	{
		if ((*Count) == 0)
		{
			delete Count;
			if (Pointer != nullptr)
			{
				Pointer -> AssignU();
			}
		}
		else
		{
			(*Count)--;
		}
	}

	Count = other.Count;
	Pointer = other.Pointer;
	if (Count != nullptr)
	{
		(*Count)++;
	}

	return *this;
}

AssignLockedChunk::AssignLockedChunk(Chunk * chunk)
	: Count(new unsigned)
	, Pointer(chunk)
{
	if (Pointer != nullptr)
	{
		(*Count) = 0;
	}
	else
	{
		delete Count;
		Count = nullptr;
	}
}

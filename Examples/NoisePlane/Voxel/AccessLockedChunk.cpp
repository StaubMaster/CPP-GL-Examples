#include "AccessLockedChunk.hpp"
#include "Chunk.hpp"



bool			AccessLockedChunk::Is() const { return (Pointer != nullptr); }
const Chunk &	AccessLockedChunk::operator*() const { return (*Pointer); }

AccessLockedChunk::~AccessLockedChunk()
{
	if (Count != nullptr)
	{
		if ((*Count) == 0)
		{
			delete Count;
			if (Pointer != nullptr)
			{
				Pointer -> AccessU();
			}
		}
		else
		{
			(*Count)--;
		}
	}
}
AccessLockedChunk::AccessLockedChunk()
	: Count(nullptr)
	, Pointer(nullptr)
{ }
AccessLockedChunk::AccessLockedChunk(const AccessLockedChunk & other)
	: Count(other.Count)
	, Pointer(other.Pointer)
{
	if (Count != nullptr)
	{
		(*Count)++;
	}
}
AccessLockedChunk & AccessLockedChunk::operator=(const AccessLockedChunk & other)
{
	if (Count != nullptr)
	{
		if ((*Count) == 0)
		{
			delete Count;
			if (Pointer != nullptr)
			{
				Pointer -> AccessU();
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

AccessLockedChunk::AccessLockedChunk(Chunk * chunk)
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

AssignLockedChunk AccessLockedChunk::ToAssign()
{
	if (Count != nullptr)
	{
		if ((*Count) == 0)
		{
			delete Count;
			Count = nullptr;
			if (Pointer != nullptr)
			{
				Chunk * chunk = Pointer;
				Pointer = nullptr;
				chunk -> AccessToAssign();
				return AssignLockedChunk(chunk);
			}
		}
		else
		{
			(*Count)--;
		}
	}
	return AssignLockedChunk();
}

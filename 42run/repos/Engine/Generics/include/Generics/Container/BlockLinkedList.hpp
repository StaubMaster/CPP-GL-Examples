#ifndef  BLOCK_LINKED_LIST_HPP
# define BLOCK_LINKED_LIST_HPP

# include "Array.hpp"

namespace Container
{
template<unsigned int BlockSize, typename TypeItem>
class BlockLinkedList
{
	public:
	struct Block
	{
		Block *		Link;
		TypeItem	Data[BlockSize];
		~Block()
		{ }
		Block()
			: Link(nullptr)
		{ }
		Block(const Block & other) = delete;
		Block & operator=(const Block & other) = delete;
	};

	private:
	unsigned int	LinkCount;
	Block *			Link;

	unsigned int	CurrentBlockItemCount;
	Block *			CurrentBlock;

	public:
	unsigned int	Count() const
	{
		return (BlockSize * LinkCount) + CurrentBlockItemCount;
	}

	public:
	const	TypeItem &		operator[](unsigned int idx) const
	{
		// if(CurrentBlockItemCount == 0) invalid
		// if(CurrentBlock == nullptr) invalid
		Block * link = Link;
		while (link != nullptr)
		{
			if (idx < BlockSize)
			{
				return link -> Data[idx];
			}
			idx -= BlockSize;
			link = link -> Link;
		}
		throw "BlockLinkedList operator[] Invalid";
	}
			TypeItem &		operator[](unsigned int idx)
	{
		Block * link = Link;
		while (link != nullptr)
		{
			if (idx < BlockSize)
			{
				return link -> Data[idx];
			}
			idx -= BlockSize;
			link = link -> Link;
		}
		throw "BlockLinkedList operator[] Invalid";
	}

	unsigned int		BlockCount() const
	{
		if (CurrentBlock == nullptr) { return 0; }
		return LinkCount + 1;
	}
	const	Block &		BlockIndex(unsigned int idx) const
	{
		Block * link = Link;
		while (link != nullptr)
		{
			if (idx == 0)
			{
				return *link;
			}
			idx--;
			link = link -> Link;
		}
		throw "BlockLinkedList BlickIndex Invalid";
	}

	public:
	~BlockLinkedList()
	{
		while (Link != nullptr)
		{
			Block * link = Link -> Link;
			delete Link;
			Link = link;
		}
	}
	BlockLinkedList()
		: LinkCount(0)
		, Link(nullptr)
		, CurrentBlockItemCount(0)
		, CurrentBlock(nullptr)
	{ }
	BlockLinkedList(const BlockLinkedList & other) = delete;
	BlockLinkedList & operator=(const BlockLinkedList & other) = delete;

	Array<TypeItem>		ToArray() const
	{
		unsigned int limit = Count();
		Array<TypeItem> array(limit);
		unsigned int count = 0;
		for (unsigned int b = 0; b < BlockCount(); b++)
		{
			const Block & block = BlockIndex(b);
			for (unsigned int i = 0; i < BlockSize; i++)
			{
				if (count < limit)
				{
					array[count] = block.Data[i];
					count++;
				}
			}
		}
		return array;
	}

	void	Clear()
	{
		while (Link != nullptr)
		{
			Block * link = Link -> Link;
			delete Link;
			Link = link;
		}
		LinkCount = 0;
		Link = nullptr;
		CurrentBlockItemCount = 0;
		CurrentBlock = nullptr;
	}

	TypeItem &	MakeNext()
	{
		if (CurrentBlock == nullptr)
		{
			Link = new Block();
			CurrentBlock = Link;
			CurrentBlockItemCount = 0;
		}
		if (CurrentBlockItemCount == BlockSize)
		{
			Block * link = new Block();
			LinkCount++;
			CurrentBlock -> Link = link;
			CurrentBlock = link;
			CurrentBlockItemCount = 0;
		}
		return CurrentBlock -> Data[CurrentBlockItemCount];
	}
	void	Next()
	{
		CurrentBlockItemCount++;
	}

	void	Insert(const TypeItem & item)
	{
		MakeNext() = item;
		Next();
	}
};
};

#endif
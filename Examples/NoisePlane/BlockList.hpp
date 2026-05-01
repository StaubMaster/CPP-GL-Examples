#ifndef  BLOCK_LIST_HPP
# define BLOCK_LIST_HPP

template<unsigned int BlockSize, typename ItemType>
class BlockList
{
	public:
	struct Block
	{
		Block *		Link;
		ItemType	Data[BlockSize];
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
	const	ItemType &		operator[](unsigned int idx) const
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
		throw "BlockList operator[] Invalid";
	}
			ItemType &		operator[](unsigned int idx)
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
		throw "BlockList operator[] Invalid";
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
		throw "BlockList BlickIndex Invalid";
	}

	public:
	~BlockList()
	{
		while (Link != nullptr)
		{
			Block * link = Link -> Link;
			delete Link;
			Link = link;
		}
	}
	BlockList()
		: LinkCount(0)
		, Link(nullptr)
		, CurrentBlockItemCount(0)
		, CurrentBlock(nullptr)
	{ }
	BlockList(const BlockList & other) = delete;
	BlockList & operator=(const BlockList & other) = delete;

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
	void	Insert(ItemType item)
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

		CurrentBlock -> Data[CurrentBlockItemCount] = item;
		CurrentBlockItemCount++;
	}
};

#endif
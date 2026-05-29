#ifndef  ACCESS_LOCKED_CHUNK_HPP
# define ACCESS_LOCKED_CHUNK_HPP

struct Chunk;
struct AssignLockedChunk;

struct AccessLockedChunk
{
	private:
	unsigned int *	Count;
	Chunk *			Pointer;

	public:
	bool			Is() const;
	const Chunk &	operator*() const;

	~AccessLockedChunk();
	AccessLockedChunk();
	AccessLockedChunk(const AccessLockedChunk & other);
	AccessLockedChunk & operator=(const AccessLockedChunk & other);

	AccessLockedChunk(Chunk * chunk);
	AssignLockedChunk	ToAssign();
};


#endif
#ifndef  ASSIGN_LOCKED_CHUNK_HPP
# define ASSIGN_LOCKED_CHUNK_HPP

struct Chunk;

struct AssignLockedChunk
{
	private:
	unsigned int *	Count;
	Chunk *			Pointer;

	public:
	bool			Is() const;
	Chunk &			operator*();

	~AssignLockedChunk();
	AssignLockedChunk();
	AssignLockedChunk(const AssignLockedChunk & other);
	AssignLockedChunk & operator=(const AssignLockedChunk & other);

	AssignLockedChunk(Chunk * chunk);
};

#endif
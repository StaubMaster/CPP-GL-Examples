#ifndef  THREAD_COLLECTION_HPP
# define THREAD_COLLECTION_HPP

# include "Generics/Container/Binary.hpp"

struct BaseLoopThread;

struct ThreadLoopCollection
{
	protected:
	Container::Binary<BaseLoopThread*>	Threads;

	private:
	bool	IsDone() const;
	void	DoTerminate();
	void	Join();

	public:
	~ThreadLoopCollection() = default;
	ThreadLoopCollection() = default;
	ThreadLoopCollection(const ThreadLoopCollection & other) = delete;
	ThreadLoopCollection & operator=(const ThreadLoopCollection & other) = delete;

	public:
	void	Run();
	void	Terminate();
};

#endif
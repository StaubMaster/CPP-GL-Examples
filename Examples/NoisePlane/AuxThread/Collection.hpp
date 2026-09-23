#ifndef  AUX_THREAD_COLLECTION_HPP
# define AUX_THREAD_COLLECTION_HPP

# include "AuxThread/0.hpp"
# include "AuxThread/1.hpp"
# include "AuxThread/2.hpp"
# include "AuxThread/3.hpp"

# include "Generics/Container/Array.hpp"

struct ContextNoisePlane;

/* Draw Thread should focus on Drawing
	avoid	locking
	move View stuff to another Thread ?
	Draw Thread needs to Create/Delete Graphics
	Input from different Thread ?
*/

struct AuxThreadCollection
{
	private:
	Container::Array<IdleLoopThread*>	Threads;
	private:
	bool	AllDone() const;

	public:
	::AuxThread0	AuxThread0;
	::AuxThread1	AuxThread1;
	::AuxThread2	AuxThread2;
	::AuxThread3	AuxThread3;

	public:
	~AuxThreadCollection() = default;
	AuxThreadCollection() = delete;
	AuxThreadCollection(const AuxThreadCollection & other) = delete;
	AuxThreadCollection & operator=(const AuxThreadCollection & other) = delete;
	AuxThreadCollection(ContextNoisePlane & context);

	public:
	void	Run();
	void	Terminate();
};

#endif
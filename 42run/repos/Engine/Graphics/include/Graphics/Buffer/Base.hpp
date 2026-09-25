#ifndef  BUFFER_BASE_HPP
# define BUFFER_BASE_HPP

# include "OpenGLTypes.hpp"

namespace Container { class Void; };

namespace Buffer
{
class Base
{
	protected:
	GL::BufferTarget		Target;
	GL::BufferDataUsage		Usage;
	GL::BufferID			ID = 0;



	public:
	/* DataWant
		new Data should be generated for this Buffer
	*/
	bool	DataWant = false;
	/* DataHave
		new Data has been generated for this Buffer
		this Buffer should take the Data
	*/
	bool	DataHave = false;
	// put these in Array and Element



	public:
	virtual ~Base();
	Base() = delete;
	Base(GL::BufferTarget target, GL::BufferDataUsage usage);

	Base(const Base & other) = default;
	Base & operator=(const Base & other) = default;



	public:
	bool	Exists() const;
	void	Create();
	void	Delete();

	public:
	void	Bind();



	public:
	void	DataNull();
	void	DataFull(unsigned int size);
	void	DataFull(const Container::Void & data);
	void	DataPart(unsigned int offset, const Container::Void & data);

	public:
	void *	DataMap();



	public:
	virtual void	LogInfo(bool self = true) const;
};
};

#endif
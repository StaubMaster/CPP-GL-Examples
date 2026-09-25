#ifndef  VERTEX_ARRAY_BASE_HPP
# define VERTEX_ARRAY_BASE_HPP

# include "Generics/Container/Binary.hpp"

# include "OpenGLTypes.hpp"

namespace VertexArray
{
class Base
{
	public:
	GL::VertexArrayID	ID = 0;



	public:
	virtual ~Base() = default;
	Base() = default;

	Base(const Base & other) = default;
	Base & operator=(const Base & other) = default;



	public:
	bool	Exists() const;
	bool	IsBound() const;
	void	Bind();

	static GL::VertexArrayID	Bound();
	static void					BindNone();



	public:
	virtual void	Create();
	virtual void	Delete();



	public:
	void	LogInfo(bool self = true) const;
};
};

#endif
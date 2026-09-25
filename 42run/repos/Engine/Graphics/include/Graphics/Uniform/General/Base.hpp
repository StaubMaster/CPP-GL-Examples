#ifndef  UNIFORM_BASE_HPP
# define UNIFORM_BASE_HPP

# include <string>

# include "OpenGLTypes.hpp"

namespace Shader { class Base; };
namespace Multiform { class Base; };

namespace Uniform
{
class Layout;
class Base
{
	public:
	std::string			Name;
	Multiform::Base *	Multiform = nullptr;
	bool				IsDynamic = false; // delete with Layout

	protected: public:
	virtual ~Base();

	private:
	Base() = delete;
	Base(const Base & other) = delete;
	Base & operator=(const Base & other) = delete;

	protected:
	Base(std::string name, bool is_dynamic);
	Base(Layout & layout, std::string name, bool is_dynamic);

	public:
	virtual void	Find(Shader::Base & shader) = 0;

	public:
	virtual void	PutVoid(const void * val) = 0;

	public:
	void	UpdateData();
	void	UpdateData(Shader::Base & shader);

	public:
	virtual void LogInfo(bool self = true) const;
};
};

#endif
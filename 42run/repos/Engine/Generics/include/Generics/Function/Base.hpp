#ifndef  GENERIC_FUNCTION_BASE_FUNCTION_HPP
# define GENERIC_FUNCTION_BASE_FUNCTION_HPP

template<typename ReturnType, typename ... Arguments>
struct BaseFunction
{
	virtual ~BaseFunction() = default;
	BaseFunction() = default;

	BaseFunction(const BaseFunction & other) = default;
	BaseFunction & operator=(const BaseFunction & other) = default;

	virtual bool		CanInvoke() const = 0;
	virtual ReturnType	Invoke(Arguments ... args) const = 0;
	virtual ReturnType	operator()(Arguments ... args) const = 0;
};

#endif
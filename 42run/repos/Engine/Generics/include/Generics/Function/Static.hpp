#ifndef  GENERIC_FUNCTION_STATIC_FUNCTION_HPP
# define GENERIC_FUNCTION_STATIC_FUNCTION_HPP

# include "Base.hpp"

template<typename ReturnType, typename ... Arguments>
struct StaticFunction : public BaseFunction<ReturnType, Arguments ...>
{
	typedef ReturnType (*FunctionType)(Arguments ...);

	private:
	FunctionType	Function = nullptr;

	public:
	~StaticFunction() = default;
	StaticFunction() = default;
	StaticFunction(const StaticFunction & other) = default;
	StaticFunction & operator=(const StaticFunction & other) = default;

	public:
	bool CanInvoke() const override
	{
		return (Function != nullptr);
	}
	ReturnType Invoke(Arguments ... args) const override
	{
		if (Function == nullptr) { throw "Function is null"; }
		return Function(args ...);
	}
	ReturnType operator()(Arguments ... args) const override
	{
		return Invoke(args ...);
	}

	public:
	StaticFunction(FunctionType func)
		: BaseFunction<ReturnType, Arguments ...>()
		, Function(func)
	{ }
	void Assign(FunctionType func)
	{
		Function = func;
	}
	void operator=(FunctionType func)
	{
		Assign(func);
	}
};

#endif
#ifndef  STATIC_CALLBACK_HPP
# define STATIC_CALLBACK_HPP

# include "Base.hpp"

template<typename ... Arguments>
struct StaticCallBack : public BaseCallBack<Arguments ...>
{
	typedef void (FunctionType)(Arguments ...);

	FunctionType &	Function;
	//void (ObjectType::*Function)();

	StaticCallBack(FunctionType & func) :
		Function(func)
	{ }
	~StaticCallBack()
	{ }

	void Run(Arguments ... args) override
	{
		Function(args ...);
	}
};

#endif
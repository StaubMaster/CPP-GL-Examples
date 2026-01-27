#ifndef  OBJECT_CALLBACK_HPP
# define OBJECT_CALLBACK_HPP

# include "Base.hpp"

template<typename ObjectType, typename ... Arguments>
struct ObjectCallBack : public BaseCallBack<Arguments ...>
{
	typedef void (ObjectType::*FunctionType)(Arguments ...);

	ObjectType *	Object;
	FunctionType	Function;
	//void (ObjectType::*Function)();

	ObjectCallBack(ObjectType * obj, FunctionType func) :
		Object(obj),
		Function(func)
	{ }
	~ObjectCallBack()
	{ }

	void Run(Arguments ... args) override
	{
		(*Object.*Function)(args ...);
	}
};

#endif
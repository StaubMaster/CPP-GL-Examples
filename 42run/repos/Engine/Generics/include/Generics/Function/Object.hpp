#ifndef  GENERIC_FUNCTION_OBJECT_FUNCTION_HPP
# define GENERIC_FUNCTION_OBJECT_FUNCTION_HPP

# include "Base.hpp"

template<typename ObjectType, typename ReturnType, typename ... Arguments>
struct ObjectFunction : public BaseFunction<ReturnType, Arguments ...>
{
	typedef ReturnType (ObjectType::*FunctionType)(Arguments ...);

	private:
	ObjectType *	Object = nullptr;
	FunctionType	Function = nullptr;

	public:
	~ObjectFunction() = default;
	ObjectFunction() = default;
	ObjectFunction(const ObjectFunction & other) = default;
	ObjectFunction & operator=(const ObjectFunction & other) = default;

	public:
	bool CanInvoke() const override
	{
		return ((Object != nullptr) && (Function != nullptr));
	}
	ReturnType Invoke(Arguments ... args) const override
	{
		if (Object == nullptr) { throw "Object is null"; }
		if (Function == nullptr) { throw "Function is null"; }
		return (*Object.*Function)(args ...);
	}
	ReturnType operator()(Arguments ... args) const override
	{
		return Invoke(args ...);
	}

	public:
	ObjectFunction(ObjectType * obj, FunctionType func)
		: BaseFunction<ReturnType, Arguments ...>()
		, Object(obj)
		, Function(func)
	{ }
	void Assign(ObjectType * obj, FunctionType func)
	{
		Object = obj;
		Function = func;
	}
	void Assign(ObjectType * obj)
	{
		Object = obj;
	}
	void Assign(FunctionType func)
	{
		Function = func;
	}
	void operator=(ObjectType * obj)
	{
		Assign(obj);
	}
	void operator=(FunctionType func)
	{
		Assign(func);
	}
};

#endif
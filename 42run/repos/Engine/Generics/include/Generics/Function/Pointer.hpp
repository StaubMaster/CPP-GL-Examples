#ifndef  GENERIC_FUNCTION_FUNCTION_POINTER_HPP
# define GENERIC_FUNCTION_FUNCTION_POINTER_HPP

# include "Base.hpp"
# include "Static.hpp"
# include "Object.hpp"

template<typename ... Arguments>
struct FunctionPointer : public BaseFunction<void, Arguments ...>
{
	private:
	unsigned int *							Count = nullptr;
	BaseFunction<void, Arguments ...> *		Function = nullptr;

	public:
	~FunctionPointer()
	{
		if (Count != nullptr)
		{
			if ((*Count) == 0)
			{
				delete Count;
				delete Function;
			}
			else
			{
				(*Count)--;
			}
		}
	}
	FunctionPointer()
		: Count(nullptr)
		, Function(nullptr)
	{ }
	FunctionPointer(const FunctionPointer & other)
		: Count(other.Count)
		, Function(other.Function)
	{
		if (Count != nullptr)
		{
			(*Count)++;
		}
	}
	FunctionPointer & operator=(const FunctionPointer & other)
	{
		if (Count != nullptr)
		{
			if ((*Count) == 0)
			{
				delete Count;
				delete Function;
			}
			else
			{
				(*Count)--;
			}
		}

		Count = other.Count;
		Function = other.Function;

		if (Count != nullptr)
		{
			(*Count)++;
		}

		return *this;
	}

	public:
	bool CanInvoke() const override
	{
		return (Function != nullptr);
	}
	void TryInvoke(Arguments ... args) const
	{
		if (Function == nullptr) { return; }
		return Function -> Invoke(args ...);
	}
	void Invoke(Arguments ... args) const override
	{
		if (Function == nullptr) { throw "FunctionBase is null"; }
		return Function -> Invoke(args ...);
	}
	void operator()(Arguments ... args) const override
	{
		Invoke(args ...);
	}

	public:
	FunctionPointer(BaseFunction<void, Arguments ...> * func)
		: Count(nullptr)
		, Function(func)
	{ }
	void Assign(BaseFunction<void, Arguments ...> * func)
	{
		if (Count != nullptr)
		{
			if ((*Count) == 0)
			{
				delete Count;
				delete Function;
			}
			else
			{
				(*Count)--;
			}
		}
	
		Count = nullptr;
		Function = func;
	}
	void operator=(BaseFunction<void, Arguments ...> * func)
	{
		Assign(func);
	}

	public:
	FunctionPointer(void (*func)(Arguments ...))
		: Count(new unsigned int)
		, Function(new StaticFunction<void, Arguments ...>(func))
	{
		(*Count) = 0;
	}
	void Assign(void (*func)(Arguments ...))
	{
		if (Count != nullptr)
		{
			if ((*Count) == 0)
			{
				delete Count;
				delete Function;
			}
			else
			{
				(*Count)--;
			}
		}

		Count = new unsigned int;
		(*Count) = 0;
		Function = new StaticFunction<void, Arguments ...>(func);
	}

	public:
	template<typename ObjectType>
	FunctionPointer(ObjectType * obj, void (ObjectType::*func)(Arguments ...))
		: Count(new unsigned int)
		, Function(new ObjectFunction<ObjectType, void, Arguments ...>(obj, func))
	{
		(*Count) = 0;
	}
	template<typename ObjectType>
	void Assign(ObjectType * obj, void (ObjectType::*func)(Arguments ...))
	{
		if (Count != nullptr)
		{
			if ((*Count) == 0)
			{
				delete Count;
				delete Function;
			}
			else
			{
				(*Count)--;
			}
		}

		Count = new unsigned int;
		(*Count) = 0;
		Function = new ObjectFunction<ObjectType, void, Arguments ...>(obj, func);
	}
	// typedef these function pointers
};

#endif
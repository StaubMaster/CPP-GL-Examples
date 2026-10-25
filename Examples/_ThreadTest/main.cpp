#include <iostream>

struct A
{
	virtual void func()
	{
		std::cout << "A::func()\n";
	}
};
struct B : public A
{
	void func() override
	{
		std::cout << "B::func()\n";
	}
};
struct C
{
	void func()
	{
		std::cout << "C::func()\n";
	}
};

template <typename TypeItem>
void func_test(
	TypeItem * obj,
	void (TypeItem::*func)(void)
)
{
	if (obj != nullptr)
	{
		(*obj.*func)();
	}
}

template <typename TypeItem, typename TypeFunc>
void func_test(
	TypeItem * obj,
	void (TypeFunc::*func)(void)
)
{
	if (obj != nullptr)
	{
		(*obj.*func)();
	}
}

int main()
{
	{
		A obj;
		func_test(&obj, A::func);
	}
	{
		B obj;
		func_test(&obj, A::func);
	}
	{
		B obj;
		func_test(&obj, B::func);
	}
	{
		A obj;
		func_test(&obj, C::func);
	}
	return 0;
}

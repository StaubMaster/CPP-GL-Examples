#include <iostream>

template<float DefaultValue>
struct sTest0
{
	void func(float val)
	{
		std::cout << "sTest0func" << ' ' << val << ' ' << DefaultValue << '\n';
	}
};

int main()
{
	std::cout << '\n';
	{
		sTest0<123> obj;
		obj.func(3.3f);
	}
	std::cout << '\n';
	return 0;
}

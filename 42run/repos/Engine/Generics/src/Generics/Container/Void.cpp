#include "Generics/Container/Void.hpp"



bool Container::Void::IsNull() const
{
	return (Data == nullptr);
}
void Container::Void::Clear()
{
	Size = 0;
	Data = nullptr;
}

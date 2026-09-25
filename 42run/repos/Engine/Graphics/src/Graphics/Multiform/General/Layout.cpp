#include "Graphics/Multiform/General/Layout.hpp"
#include "Graphics/Multiform/General/Base.hpp"
#include "Graphics/Uniform/General/Layout.hpp"



Multiform::Layout::~Layout()
{ }
Multiform::Layout::Layout()
{ }



void Multiform::Layout::Find(Uniform::Layout & layout)
{
	for (unsigned int i = 0; i < Multiforms.Count(); i++)
	{
		Multiforms[i] -> FindUniforms(layout);
	}
}
void Multiform::Layout::Find(Uniform::Layout * layout)
{
	for (unsigned int i = 0; i < Multiforms.Count(); i++)
	{
		Multiforms[i] -> FindUniforms(layout);
	}
}
void Multiform::Layout::Find(Container::Array<Uniform::Layout*> & layouts)
{
	for (unsigned int i = 0; i < Multiforms.Count(); i++)
	{
		Multiforms[i] -> FindUniforms(layouts);
	}
}

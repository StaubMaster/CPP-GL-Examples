#include "Graphics/Multiform/General/Base.hpp"

#include "Graphics/Uniform/General/Base.hpp"
#include "Graphics/Uniform/General/Layout.hpp"



Multiform::Base::Base(std::string name)
	: Name(name)
{ }
Multiform::Base::~Base()
{ }



/*void Multiform::Base::FindUniforms(Uniform::Layout & layout)
{
	for (unsigned int u = 0; u < layout.Uniforms.Count(); u++)
	{
		Uniform::Base * uni = layout.Uniforms[u];
		if (uni -> Name == this -> Name)
		{
			uni -> Multiform = this;
			Uniforms.Insert(uni);
		}
	}
}*/
void Multiform::Base::FindUniforms(Uniform::Layout & layout)
{
	layout.Find(*this);
}
void Multiform::Base::FindUniforms(Uniform::Layout * layout)
{
	if (layout != nullptr)
	{
		FindUniforms(*layout);
	}
}
void Multiform::Base::FindUniforms(Container::Array<Uniform::Layout*> & layouts)
{
	for (unsigned int i = 0; i < layouts.Length(); i++)
	{
		FindUniforms(layouts[i]);
	}
}



void Multiform::Base::PutUniformThis()
{
	for (unsigned int i = 0; i < Uniforms.Count(); i++)
	{
		Uniforms[i] -> Multiform = this;
	}
}

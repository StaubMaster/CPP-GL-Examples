#include "Graphics/Uniform/General/FloatNBase.hpp"
#include "Graphics/Uniform/General/Layout.hpp"
#include "Graphics/Shader/Base.hpp"



Uniform::FloatNBase::~FloatNBase()
{ }

Uniform::FloatNBase::FloatNBase(std::string name, bool is_dynamic)
	: Base(name, is_dynamic)
{ }
Uniform::FloatNBase::FloatNBase(Uniform::Layout & layout, std::string name, bool is_dynamic)
	: Base(layout, name, is_dynamic)
{ }



void Uniform::FloatNBase::Find(Shader::Base & shader)
{
	Index = shader.FindUniformLocation(Name.c_str());
}



void Uniform::FloatNBase::PutVoid(const void * val)
{
	/*if (!Layout.IsBound())
	{
		Layout.Bind();
	}*/
	PutData((const float *)val);
}

#include "Graphics/Uniform/General/UIntNBase.hpp"
#include "Graphics/Uniform/General/Layout.hpp"
#include "Graphics/Shader/Base.hpp"



Uniform::UIntNBase::~UIntNBase()
{ }

Uniform::UIntNBase::UIntNBase(std::string name, bool is_dynamic)
	: Base(name, is_dynamic)
{ }
Uniform::UIntNBase::UIntNBase(Uniform::Layout & layout, std::string name, bool is_dynamic)
	: Base(layout, name, is_dynamic)
{ }



void Uniform::UIntNBase::Find(Shader::Base & shader)
{
	Index = shader.FindUniformLocation(Name.c_str());
}



void Uniform::UIntNBase::PutVoid(const void * val)
{
	/*if (!Layout.IsBound())
	{
		Layout.Bind();
	}*/
	PutData((const unsigned int *)val);
}

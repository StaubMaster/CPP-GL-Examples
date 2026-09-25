#include "Graphics/Uniform/General/Base.hpp"
#include "Graphics/Uniform/General/Layout.hpp"
#include "Graphics/Multiform/General/Base.hpp"



Uniform::Base::~Base()
{ }
Uniform::Base::Base(std::string name, bool is_dynamic)
	: Name(name)
	, Multiform(nullptr)
	, IsDynamic(is_dynamic)
{ }
Uniform::Base::Base(Uniform::Layout & layout, std::string name, bool is_dynamic)
	: Name(name)
	, Multiform(nullptr)
	, IsDynamic(is_dynamic)
{
	layout.Put(this);
}



void Uniform::Base::UpdateData()
{
	if (Multiform != nullptr)
	{
		Multiform -> PutData(*this);
	}
}
void Uniform::Base::UpdateData(Shader::Base & shader)
{
	if (Multiform != nullptr)
	{
		Multiform -> PutData(*this, shader);
	}
}

#include "Graphics/Uniform/General/Layout.hpp"
#include "Graphics/Uniform/General/Base.hpp"

#include "Graphics/Shader/Base.hpp"



void Uniform::Layout::Clear()
{
	for (unsigned int i = 0; i < Uniforms.Count(); i++)
	{
		if (Uniforms[i] -> IsDynamic)
		{
			delete Uniforms[i];
		}
	}
	Uniforms.Clear();
}
void Uniform::Layout::Put(Uniform::Base & uniform)
{
	Uniforms.Insert(&uniform);
}
void Uniform::Layout::Put(Uniform::Base * uniform)
{
	if (uniform != nullptr)
	{
		Uniforms.Insert(uniform);
	}
}



/*
[0]		DisplaySize
[1]		DisplaySize.Ratio
[2]		DisplaySize.Window
[3]		DisplaySize.Buffer

[0].IsDynamic
	delete[0]
[1].IsDynamic	segfault
*/
Uniform::Layout::~Layout()
{
	unsigned int prev = 0xFFFFFFFF;
	unsigned int next = 0xFFFFFFFF;

	for (unsigned int i = 0; i < Uniforms.Count(); i++)
	{
		if (Uniforms[i] -> IsDynamic)
		{
			next = i;
			break;
		}
	}

	while (next != 0xFFFFFFFF)
	{
		prev = next;
		next = 0xFFFFFFFF;
		for (unsigned int i = prev + 1; i < Uniforms.Count(); i++)
		{
			if (Uniforms[i] -> IsDynamic)
			{
				next = i;
				break;
			}
		}
		delete Uniforms[prev];
	}

	/*for (unsigned int i = 0; i < Uniforms.Count(); i++)
	{
		if (Uniforms[i] -> IsDynamic)
		{
			delete Uniforms[i];
		}
	}*/
}
Uniform::Layout::Layout()
	: Shader(nullptr)
{ }
Uniform::Layout::Layout(Shader::Base & shader)
	: Shader(&shader)
{ }

Uniform::Layout::Layout(const Layout & other)
	: Shader(other.Shader)
{ }



bool Uniform::Layout::IsBound() const
{
	if (Shader != nullptr)
	{
		return Shader -> IsBound();
	}
	return false;
}
void Uniform::Layout::Bind()
{
	if (Shader != nullptr)
	{
		Shader -> Bind();
	}
}



void Uniform::Layout::Find()
{
	if (Shader == nullptr) { return; }
	for (unsigned int i = 0; i < Uniforms.Count(); i++)
	{
		Uniforms[i] -> Find(*Shader);
	}
}



#include "Graphics/Multiform/General/Base.hpp"
void Uniform::Layout::Find(Multiform::Base & multiform)
{
	for (unsigned int i = 0; i < Uniforms.Count(); i++)
	{
		Uniform::Base * uniform = Uniforms[i];
		if (multiform.Name == uniform -> Name)
		{
			multiform.Uniforms.Insert(uniform);
		}
	}
}





void Uniform::Layout::UpdateData()
{
	for (unsigned int i = 0; i < Uniforms.Count(); i++)
	{
		Uniforms[i] -> UpdateData();
	}
	if (Shader != nullptr)
	{
		for (unsigned int i = 0; i < Uniforms.Count(); i++)
		{
			Uniforms[i] -> UpdateData(*Shader);
		}
	}
}

#include "Graphics/Uniform/General/Buffer.hpp"
void Uniform::Layout::Bind(Buffer & uniform, GL::BlockBinding binding)
{
	if (Shader != nullptr)
	{
		Shader -> BindUniformBlockIndex(uniform.Index, binding);
	}
}

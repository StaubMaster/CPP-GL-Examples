#include "OpenGL.hpp"
#include "Debug.hpp"
#include <sstream>

#include "Graphics/Uniform/General/Base.hpp"
#include "Graphics/Uniform/General/FloatNBase.hpp"
#include "Graphics/Uniform/General/UIntNBase.hpp"
#include "Graphics/Uniform/General/Buffer.hpp"
#include "Graphics/Uniform/General/Layout.hpp"



void Uniform::Base::LogInfo(bool self) const
{
	if (self)
	{
		Debug::Log << Debug::Tabs << "Uniform Info\n";
		Debug::Log << Debug::TabInc;
	}
	Debug::Log << Debug::Tabs << '"' << (Name) << '"' << '\n';
	if (self)
	{
		Debug::Log << Debug::TabDec;
		Debug::Log << Debug::Done;
	}
}

void Uniform::FloatNBase::LogInfo(bool self) const
{
	if (self)
	{
		Debug::Log << Debug::Tabs << "Uniform Location Info\n";
		Debug::Log << Debug::TabInc;
	}
	Debug::Log << Debug::Tabs << '"' << (Name) << '"';
	Debug::Log << ':';
	if (Index == -1)
	{
		Debug::Log << '!';
	}
	else
	{
		Debug::Log << Index;
	}
	Debug::Log << '\n';
	if (self)
	{
		Debug::Log << Debug::TabDec;
		Debug::Log << Debug::Done;
	}
}

void Uniform::UIntNBase::LogInfo(bool self) const
{
	if (self)
	{
		Debug::Log << Debug::Tabs << "Uniform Location Info\n";
		Debug::Log << Debug::TabInc;
	}
	Debug::Log << Debug::Tabs << '"' << (Name) << '"';
	Debug::Log << ':';
	if (Index == -1)
	{
		Debug::Log << '!';
	}
	else
	{
		Debug::Log << Index;
	}
	Debug::Log << '\n';
	if (self)
	{
		Debug::Log << Debug::TabDec;
		Debug::Log << Debug::Done;
	}
}

void Uniform::Buffer::LogInfo(bool self) const
{
	if (self)
	{
		Debug::Log << Debug::Tabs << "Uniform Index Info\n";
		Debug::Log << Debug::TabInc;
	}
	Debug::Log << Debug::Tabs << '"' << (Name) << '"';
	Debug::Log << ':';
	if (Index == GL_INVALID_INDEX)
	{
		Debug::Log << '!';
	}
	else
	{
		Debug::Log << Index;
	}
	Debug::Log << '\n';
	if (self)
	{
		Debug::Log << Debug::TabDec;
		Debug::Log << Debug::Done;
	}
}

void Uniform::Layout::LogInfo() const
{
	Debug::Log << Debug::Tabs << "Uniform::Layout\n";
	Debug::Log << Debug::Tabs << "{\n";
	Debug::Log << Debug::TabInc;
	Debug::Log << Debug::Tabs << "Uniforms[" << Uniforms.Count() << "]\n";
	Debug::Log << Debug::Tabs << "[\n";
	Debug::Log << Debug::TabInc;
	for (unsigned int i = 0; i < Uniforms.Count(); i++)
	{
		Uniforms[i] -> LogInfo(false);
	}
	Debug::Log << Debug::TabDec;
	Debug::Log << Debug::Tabs << "]\n";
	Debug::Log << Debug::TabDec;
	Debug::Log << Debug::Tabs << "}\n";
}

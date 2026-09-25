#include "OpenGL.hpp"
#include "Debug.hpp"
#include <sstream>

#include "Graphics/Buffer/Base.hpp"
#include "Graphics/Buffer/Array.hpp"
#include "Graphics/Buffer/Element.hpp"
#include "Graphics/Buffer/Uniform.hpp"

#include "Graphics/Attribute/General/Layout.hpp"

#include "Graphics/VertexArray/Base.hpp"



void Buffer::Base::LogInfo(bool self) const
{
	(void)self;
	if (self)
	{
		Debug::Log << Debug::Tabs << "Buffer Info\n";
		Debug::Log << Debug::TabInc;
	}
	Debug::Log << Debug::Tabs << "ID " << ID << '\n';
	if (self)
	{
		Debug::Log << Debug::TabDec;
		Debug::Log << Debug::Done;
	}
}

void Buffer::Array::LogInfo(bool self) const
{
	(void)self;
	Debug::Log << Debug::Tabs << "Buffer::Array\n";
	Debug::Log << Debug::Tabs << "{\n";
	Debug::Log << Debug::TabInc;
	Debug::Log << Debug::Tabs << "ID: " << ID << '\n';
	Debug::Log << Debug::Tabs << "Usade: " << Usage << '\n';
	/*if (AttributeLayout != nullptr)
	{
		AttributeLayout -> LogInfo();
	}
	else
	{
		Debug::Log << Debug::Tabs << "Missing Layout\n";
	}*/
	Debug::Log << Debug::TabDec;
	Debug::Log << Debug::Tabs << "}\n";
}

void Buffer::Element::LogInfo(bool self) const
{
	(void)self;
	Debug::Log << Debug::Tabs << "Buffer::Element\n";
	Debug::Log << Debug::Tabs << "{\n";
	Debug::Log << Debug::TabInc;
	Debug::Log << Debug::Tabs << "ID: " << ID << '\n';
	Debug::Log << Debug::Tabs << "Usade: " << Usage << '\n';
	Debug::Log << Debug::Tabs << "IndexType: " << IndexType << '\n';
	Debug::Log << Debug::TabDec;
	Debug::Log << Debug::Tabs << "}\n";
}

void Buffer::Uniform::LogInfo(bool self) const
{
	(void)self;
	Debug::Log << Debug::Tabs << "Buffer::Uniform\n";
	Debug::Log << Debug::Tabs << "{\n";
	Debug::Log << Debug::TabInc;
	Debug::Log << Debug::Tabs << "ID: " << ID << '\n';
	Debug::Log << Debug::Tabs << "Usade: " << Usage << '\n';
	Debug::Log << Debug::TabDec;
	Debug::Log << Debug::Tabs << "}\n";
}

void VertexArray::Base::LogInfo(bool self) const
{
	(void)self;
	if (self)
	{
		Debug::Log << Debug::Tabs << "NSVertexArray\n";
		Debug::Log << Debug::Tabs << "{\n";
		Debug::Log << Debug::TabInc;
	}
	Debug::Log << Debug::Tabs << "ID " << ID << '\n';
	if (self)
	{
		Debug::Log << Debug::TabDec;
		Debug::Log << Debug::Tabs << "}\n";
		Debug::Log << Debug::Done;
	}
}

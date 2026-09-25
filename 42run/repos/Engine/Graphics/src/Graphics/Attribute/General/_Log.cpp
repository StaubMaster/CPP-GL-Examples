#include "OpenGL.hpp"
#include "Debug.hpp"
#include <sstream>

#include "Graphics/Attribute/General/Base.hpp"
#include "Graphics/Attribute/General/FloatNBase.hpp"
#include "Graphics/Attribute/General/UIntNBase.hpp"
#include "Graphics/Attribute/General/IntNBase.hpp"
#include "Graphics/Attribute/General/Layout.hpp"



void Attribute::Base::LogInfo() const { }

void Attribute::FloatNBase::LogInfoBase(GL::AttributeType type, unsigned int size0, unsigned int size1) const
{
	//Debug::Log << Debug::Tabs << "Attribute::Location:" << " Type: " << GL::AttributeType::Float << " Size0: " << Size0 << " Size1: " << Size1 << " Offset: " << (Size0 * sizeof(float));
	Debug::Log << Debug::Tabs;
	Debug::Log << type << '*' << size0 << '*' << size1;
	//Debug::Log << (Size0 * sizeof(float));
	//Debug::Log << " Index:";
	for (unsigned int s = 0; s < size1; s++)
	{
		Debug::Log << ':' << (Index + s);
	}
	Debug::Log << '\n';
}
void Attribute::UIntNBase::LogInfoBase(GL::AttributeIntType type, unsigned int size0, unsigned int size1) const
{
	//Debug::Log << Debug::Tabs << "Attribute::Location:" << " Type: " << GL::AttributeType::Float << " Size0: " << Size0 << " Size1: " << Size1 << " Offset: " << (Size0 * sizeof(float));
	Debug::Log << Debug::Tabs;
	Debug::Log << type << '*' << size0 << '*' << size1;
	//Debug::Log << (Size0 * sizeof(float));
	//Debug::Log << " Index:";
	for (unsigned int s = 0; s < size1; s++)
	{
		Debug::Log << ':' << (Index + s);
	}
	Debug::Log << '\n';
}
void Attribute::IntNBase::LogInfoBase(GL::AttributeIntType type, unsigned int size0, unsigned int size1) const
{
	//Debug::Log << Debug::Tabs << "Attribute::Location:" << " Type: " << GL::AttributeType::Float << " Size0: " << Size0 << " Size1: " << Size1 << " Offset: " << (Size0 * sizeof(float));
	Debug::Log << Debug::Tabs;
	Debug::Log << type << '*' << size0 << '*' << size1;
	//Debug::Log << (Size0 * sizeof(float));
	//Debug::Log << " Index:";
	for (unsigned int s = 0; s < size1; s++)
	{
		Debug::Log << ':' << (Index + s);
	}
	Debug::Log << '\n';
}

void Attribute::Layout::LogInfo() const
{
	Debug::Log << Debug::Tabs << "Attribute::Layout\n";
	Debug::Log << Debug::Tabs << "{\n";
	Debug::Log << Debug::TabInc;
	Debug::Log << Debug::Tabs << "Divisor: " << Divisor << '\n';
	Debug::Log << Debug::Tabs << "Stride: " << Stride << '\n';
	Debug::Log << Debug::Tabs << "Attributes[" << Attributes.Count() << "]\n";
	Debug::Log << Debug::Tabs << "[\n";
	Debug::Log << Debug::TabInc;
	for (unsigned int i = 0; i < Attributes.Count(); i++)
	{
		Attributes[i] -> LogInfo();
	}
	Debug::Log << Debug::TabDec;
	Debug::Log << Debug::Tabs << "]\n";
	Debug::Log << Debug::TabDec;
	Debug::Log << Debug::Tabs << "}\n";
}

#include "Graphics/VertexArray/Base.hpp"
#include "OpenGL.hpp"



bool VertexArray::Base::Exists() const { return (ID != 0); }
bool VertexArray::Base::IsBound() const { return (Bound() == ID); }
void VertexArray::Base::Bind()
{
	if (Exists() && !IsBound())
	{
		GL::BindVertexArray(ID);
	}
}

GL::VertexArrayID VertexArray::Base::Bound()
{
	return GL::GetIntegerv(GL::ParameterName::VertexArrayBinding);
}
void VertexArray::Base::BindNone()
{
	GL::BindVertexArray(0);
}



#include "Debug.hpp"
#include <sstream>

void VertexArray::Base::Create()
{
	if (ID != 0) { return; }

	Debug::Log << "VertexArray Creating " << ID << " ..." << Debug::Done;
	ID = GL::CreateVertexArray();
	Debug::Log << "VertexArray Creating " << ID << " done" << Debug::Done;

	Debug::Log << "Create VertexArray: " << ID << Debug::Done;
	LogInfo();
}
void VertexArray::Base::Delete()
{
	if (ID == 0) { return; }

	Debug::Log << "Delete BufferArray: " << ID << Debug::Done;
	LogInfo();

	Debug::Log << "VertexArray Deleting " << ID << " ..." << Debug::Done;
	GL::DeleteVertexArray(ID);
	ID = 0;
	Debug::Log << "VertexArray Deleting " << ID << " done" << Debug::Done;
}



/*void VertexArray::Base::ChangeAttributeLayoutMain(Attribute::Layout & layout)
{
	AttributeLayoutMain = &layout;
	AttributeLayoutMainBound = false;
}
void VertexArray::Base::ChangeAttributeLayoutMain(Attribute::Layout * layout)
{
	if (layout != nullptr)
	{
		ChangeAttributeLayoutMain(*layout);
	}
}
void VertexArray::Base::ChangeAttributeLayoutInst(Attribute::Layout & layout)
{
	AttributeLayoutInst = &layout;
	AttributeLayoutInstBound = false;
}
void VertexArray::Base::ChangeAttributeLayoutInst(Attribute::Layout * layout)
{
	if (layout != nullptr)
	{
		ChangeAttributeLayoutInst(*layout);
	}
}
void VertexArray::Base::InitAttributeLayoutMain(Buffer::Array & buffer)
{
	buffer.Bind();
	if (!AttributeLayoutMainBound)
	{
		if (AttributeLayoutMain != nullptr)
		{
			AttributeLayoutMain -> Bind();
			AttributeLayoutMainBound = true;
		}
	}
}
void VertexArray::Base::InitAttributeLayoutInst(Buffer::Array & buffer)
{
	buffer.Bind();
	if (!AttributeLayoutInstBound)
	{
		if (AttributeLayoutInst != nullptr)
		{
			AttributeLayoutInst -> Bind();
			AttributeLayoutInstBound = true;
		}
	}
}*/

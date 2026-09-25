#include "Graphics/Shader/Base.hpp"
#include "Graphics/Shader/Code.hpp"

#include "Graphics/Uniform/General/Layout.hpp"

#include "OpenGL.hpp"
#include "Debug.hpp"
#include <sstream>



Shader::Base::~Base()
{
	// this will segfault if Shader Copies
	// eighter = delete Shader Copying
	// or make this another Counting thing
	// maybe make a generic Counting thing
	// that is just std::shared_ptr
	// but I dont like some of the functionality of those
	// also some basic functions they only get in c++23 or something
	if (Layout != nullptr)
	{
		if (Layout -> IsDynamic)
		{
			delete Layout;
		}
	}
}
/*Shader::Base::Base()
	: ID(0)
	, Code()
	, Layout(nullptr)
{ }*/
/*Shader::Base::Base(const Shader::Base & other)
	: ID(other.ID)
	, Code(other.Code)
	, Layout(other.Layout)
{ }*/
/*Shader::Base & Shader::Base::operator=(const Shader::Base & other)
{
	ID = other.ID;
	Code = other.Code;
	Layout = other.Layout;
	return *this;
}*/



GL::ShaderID Shader::Base::Bound()
{
	return GL::GetIntegerv(GL::ParameterName::CurrentProgram);
}
void Shader::Base::BindNone()
{
	GL::UseProgram(0);
}

bool Shader::Base::IsBound() const
{
	return (Bound() == ID);
}
void Shader::Base::Bind()
{
	if (Exists() && !IsBound())
	{
		GL::UseProgram(ID);
		if (Layout != nullptr)
		{
			Layout -> UpdateData();
		}
	}
}



bool Shader::Base::Validate() const
{
	GL::ValidateProgram(ID);
	return (GL::GetProgramiv(ID, GL::ShaderProgramParameterName::ValidateStatus));
}
bool Shader::Base::Exists() const
{
	if (ID == 0)
	{
		return false;
	}
	if (GL::GetProgramiv(ID, GL::ShaderProgramParameterName::InfoLogLength) != 0)
	{
		return false;
	}
	if (GL::GetProgramiv(ID, GL::ShaderProgramParameterName::LinkStatus) == 0)
	{
		return false;
	}
	return true;
}
void Shader::Base::Delete()
{
	if (ID == 0) { return; }

	Debug::Log << "Delete Shader: " << ID << Debug::Done;
	LogInfo();

	Debug::Log << "Shader::Base Deleting " << ID << " ..." << Debug::Done;
	GL::DeleteProgram(ID);
	ID = 0;
	Debug::Log << "Shader::Base Deleting " << ID << " done" << Debug::Done;

	if (Layout != nullptr)
	{
		Layout -> Find();
	}
}
void Shader::Base::Create()
{
	if (ID != 0) { return; }

	Debug::Log << "Shader::Base Creating " << ID << " ..." << Debug::Done;
	ID = GL::CreateProgram();

	Shader::Code::Compile(Code);
	if (Shader::Code::Valid(Code))
	{
		Shader::Code::Attach(Code, ID);
		GL::LinkProgram(ID);
		Shader::Code::Detach(Code, ID);
	}
	else
	{
		Debug::Log << Debug::Tabs << "Shader::Code[" << Code.Length() << "]\n";
		Debug::Log << Debug::TabInc;
		for (unsigned int i = 0; i < Code.Length(); i++)
		{
			Debug::Log << Debug::Tabs << "[" << i << "]\n";
			Debug::Log << Debug::TabInc;
			Code[i].LogInfo(false, true);
			Debug::Log << Debug::TabDec;
		}
		Debug::Log << Debug::TabDec;
		Debug::Log << Debug::Done;
	}
	Shader::Code::Dispose(Code);

	/*char log_arr[1024];
	int log_len = 0;
	glGetProgramInfoLog(ID, 1024, &log_len, log_arr);
	if (log_len != 0)
	{
		std::string log = std::string(log_arr, log_len);
		throw ECompileLog(log);
	}*/

	//Debug::Log << "Shader::Base Creating " << ID << " done" << Debug::Done;

	if (Layout != nullptr)
	{
		Layout -> Find();
	}

	Debug::Log << "Create Shader: " << ID << Debug::Done;
	LogInfo(true, true);
}

void Shader::Base::Change(const Container::Array<Shader::Code> & code)
{
	if (Exists())
	{
		Delete();
		Code = code;
		Create();
	}
	else
	{
		Code = code;
	}
}
void Shader::Base::Change(const Container::Array<FileInfo> & files)
{
	Container::Array<Shader::Code> code(files.Length());
	for (unsigned int i = 0; i < code.Length(); i++)
	{
		code[i] = Shader::Code(files[i]);
	}
	Change(code);
}
void Shader::Base::Change(std::initializer_list<Shader::Code> code)
{
	Change(Container::Array<Shader::Code>(code));
}
void Shader::Base::Change(std::initializer_list<FileInfo> files)
{
	Change(Container::Array<FileInfo>(files));
}



void Shader::Base::AssignLayout(Uniform::Layout & layout)
{
	Layout = &layout;
	layout.Shader = this;
}
void Shader::Base::AssignLayout(Uniform::Layout * layout)
{
	Layout = layout;
	if (layout != nullptr)
	{
		layout -> Shader = this;
	}
}



GL::UniformLocation Shader::Base::FindUniformLocation(const char * name) const
{
	if (Exists())
	{
		return GL::GetUniformLocation(ID, name);
	}
	else
	{
		return -1;
	}
}
GL::BlockIndex Shader::Base::FindUniformBlockIndex(const char * name) const
{
	if (Exists())
	{
		return GL::GetUniformBlockIndex(ID, name);
	}
	else
	{
		return -1;
	}
}

void Shader::Base::BindUniformBlockIndex(GL::BlockIndex index, GL::BlockBinding binding)
{
	GL::UniformBlockBinding(ID, index, binding);
}



Shader::Base::ECompileLog::ECompileLog(const std::string log)
{
	Log = log;
	Text = "Log returned from compiling File.\n\n" + Log;
}
const char * Shader::Base::ECompileLog::what() const throw()
{
	return Text.c_str();
}

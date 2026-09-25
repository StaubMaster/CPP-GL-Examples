#include "OpenGL.hpp"
#include "Debug.hpp"
#include <sstream>

#include "Graphics/Shader/Base.hpp"
#include "Graphics/Shader/Code.hpp"

#include "Graphics/Uniform/General/Base.hpp"
#include "Graphics/Uniform/General/Layout.hpp"



void Shader::Base::LogInfo(bool self, bool log) const
{
	if (self)
	{
		Debug::Log << Debug::Tabs << "Shader Info\n";
		Debug::Log << Debug::Tabs << "{\n";
		Debug::Log << Debug::TabInc;
	}
	Debug::Log << Debug::Tabs << "ID " << ID << '\n';

	Debug::Log << Debug::Tabs << "Code[" << Code.Length() << "]\n";
	Debug::Log << Debug::Tabs << "[\n";
	Debug::Log << Debug::TabInc;
	for (unsigned int i = 0; i < Code.Length(); i++) { Code[i].LogInfo(false); }
	Debug::Log << Debug::TabDec;
	Debug::Log << Debug::Tabs << "]\n";

	if (Layout != nullptr)
	{
		Layout -> LogInfo();
	}
	else
	{
		Debug::Log << Debug::Tabs << "Missing Layout\n";
	}

	{
		if (ID != 0)
		{
			int len = GL::GetProgramiv(ID, GL::ShaderProgramParameterName::InfoLogLength);
			Debug::Log << Debug::Tabs << "InfoLog: " << len << '\n';
			if (log && len != 0)
			{
				char str[len];
				GL::GetProgramInfoLog(ID, len, len, str);
				Debug::Log << "####\n";
				Debug::Log << str;
				Debug::Log << "####\n";
			}
			unsigned int status = GL::GetProgramiv(ID, GL::ShaderProgramParameterName::LinkStatus);
			Debug::Log << Debug::Tabs << "Status: " << status << '\n';
		}
		else
		{
			Debug::Log << Debug::Tabs << "InfoLog:\n";
			Debug::Log << Debug::Tabs << "Status:\n";
		}
	}

	if (self)
	{
		Debug::Log << Debug::TabDec;
		Debug::Log << Debug::Tabs << "}\n";
		Debug::Log << Debug::Done;
	}
}

void Shader::Code::LogInfo(bool self, bool log) const
{
	if (self)
	{
		Debug::Log << Debug::Tabs << "Shader Info\n";
		Debug::Log << Debug::TabInc;
	}
	//Debug::Log << Debug::Tabs << "Type " << typeid(*this).name() << '\n';
	Debug::Log << Debug::Tabs << "ID: " << ID << '\n';
	Debug::Log << Debug::Tabs << "Type: " << Type << '\n';
	Debug::Log << Debug::Tabs << "File: " << File.Path.ToString() << '\n';
	{
		if (ID != 0)
		{
			int len = GL::GetShaderiv(ID, GL::ShaderParameterName::InfoLogLength);
			Debug::Log << Debug::Tabs << "InfoLog: " << len << '\n';
			if (log && len != 0)
			{
				char str[len];
				glGetShaderInfoLog(ID, len, &len, str);
				Debug::Log << "####\n";
				Debug::Log << str;
				Debug::Log << "####\n";
			}
			unsigned int status = GL::GetShaderiv(ID, GL::ShaderParameterName::CompileStatus);
			Debug::Log << Debug::Tabs << "Status: " << status << '\n';
		}
		else
		{
			Debug::Log << Debug::Tabs << "InfoLog:\n";
			Debug::Log << Debug::Tabs << "Status:\n";
		}
	}
	if (self)
	{
		Debug::Log << Debug::TabDec;
		Debug::Log << Debug::Done;
	}
}

#include "FileParsing/Variables/Float.hpp"



ParsingVariable::Float::Float(std::string name, float value)
	: Name(name)
	, Value(value)
{ }

bool ParsingVariable::Float::IsLiteral(std::string str)
{
	// only a partial check for now

	if (str.size() == 0) { return false; }

	char c = str[0];

	if (c == '+' || c == '-')
	{
		if (str.size() == 1) { return false; }
		c = str[1];
	}

	if (c >= '0' && c <= '9')
	{
		return true;
	}

	return false;
}
float ParsingVariable::Float::ParseLiteral(std::string str)
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] == ',') { str[i] = '.'; }
	}
	return std::stof(str);
}

char ParsingVariable::Float::SignTake(std::string & str)
{
	if (str.size() == 0) { return '\0'; }

	char sign = str[0];
	if (sign != '+' && sign != '-')
	{
		return '\0';
	}
	else
	{
		str.erase(0, 1);
	}
	return sign;

}
float ParsingVariable::Float::SignPut(float value, char sign)
{
	if (sign == '+') { return +value; }
	if (sign == '-') { return -value; }
	return value;
}



ParsingVariable::Float * ParsingVariable::FloatMemory::Find(std::string name)
{
	for (unsigned int i = 0; i < Variables.Count(); i++)
	{
		if (Variables[i].Name == name)
		{
			return &Variables[i];
		}
	}
	return nullptr;
}
const ParsingVariable::Float * ParsingVariable::FloatMemory::Find(std::string name) const
{
	for (unsigned int i = 0; i < Variables.Count(); i++)
	{
		if (Variables[i].Name == name)
		{
			return &Variables[i];
		}
	}
	return nullptr;
}

void ParsingVariable::FloatMemory::Put(std::string name, float value)
{
	Float * var = Find(name);
	if (var != nullptr)
	{
		var -> Value = value;
	}
	else
	{
		Variables.Insert(Float(name, value));
	}
}
float ParsingVariable::FloatMemory::To(std::string str) const
{
	const Float * var = Find(str);
	if (var == nullptr) { return 0.0f; } // return NaN ?
	return var -> Value;
}

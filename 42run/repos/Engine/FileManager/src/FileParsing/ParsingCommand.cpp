#include "FileParsing/ParsingCommand.hpp"



ParsingCommand::ParsingCommand(std::string text)
{
	std::stringstream ss(text);
	std::string seg;
	while (std::getline(ss, seg, ' '))
	{
		seg = StringHelp::RemoveFromString(seg, StringHelp::CharPallet(" \t"));
		Segments.push_back(seg);
	}
}

std::string ParsingCommand::Name() const
{
	if (Segments.size() == 0) { return ""; }
	return Segments[0];
}
unsigned int ParsingCommand::Count() const
{
	if (Segments.size() == 0) { return 0; }
	return Segments.size() - 1;
}
bool ParsingCommand::CheckCount(const CountCheck & check) const
{
	return check.Check(Count());
}



std::string		ParsingCommand::ToString(unsigned int idx) const
{
	if (idx >= Segments.size() - 1) { return ""; }
	return Segments[idx + 1];
}
float			ParsingCommand::ToFloat(unsigned int idx) const
{
	if (idx >= Segments.size() - 1) { return 0.0f; }
	std::string str = Segments[idx + 1];
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] == ',') { str[i] = '.'; }
	}
	return std::stof(str);
}
unsigned int	ParsingCommand::ToUInt32(unsigned int idx) const
{
	if (idx >= Segments.size() - 1) { return 0; }
	return std::stoul(Segments[idx + 1]);
}
int				ParsingCommand::ToInt32(unsigned int idx) const
{
	if (idx >= Segments.size() - 1) { return 0; }
	return std::stoi(Segments[idx + 1]);
}





ParsingCommand::ExceptionUnknownName::ExceptionUnknownName(const ParsingCommand & cmd)
{
	std::ostringstream oss;
	oss << "Unknown Command Name: '" << cmd.Name() << "'.";
	Text = oss.str();
}
ParsingCommand::ExceptionInvalidCount::ExceptionInvalidCount(const ParsingCommand & cmd, const CountCheck & check)
{
	std::ostringstream oss;
	oss << "Invalid Argument Count in Command: '" << cmd.Name() << "'. ";
	oss << "Argument Count: [" << cmd.Count() << "] ";
	oss << "Check: " << check.ToString() << ".";
	Text = oss.str();
}
ParsingCommand::ExceptionInvalidArg::ExceptionInvalidArg(const ParsingCommand & cmd, unsigned int idx)
{
	std::ostringstream oss;
	oss << "Invalid Argument in Command: '" << cmd.Name() << "'. ";
	oss << "Argument: [" << idx << "] '" << cmd.ToString(idx) << "'.";
	Text = oss.str();
}



std::ostream & operator <<(std::ostream & os, const ParsingCommand & obj)
{
	os << obj.Name();
	for (unsigned int i = 0; i < obj.Count(); i++)
	{
		os << " <" << obj.ToString(i) << ">";
	}
	return os;
}





#include "FileInfo.hpp"

ParsingCommand::EnvironmentData::EnvironmentData(const FileInfo & file) :
	File(file) { }

void ParsingCommand::SplitFileIntoCommands(EnvironmentData & data)
{
	std::stringstream ss(data.File.LoadText());
	std::string seg;
	while (std::getline(ss, seg, '\n'))
	{
		seg = StringHelp::RemoveFromString(seg, StringHelp::CharPallet("\n\r"));
		seg = StringHelp::RemoveFromString(seg, StringHelp::CharPallet("#"), StringHelp::CharPallet("\n"));
		data.Parse(ParsingCommand(seg));
	}
}

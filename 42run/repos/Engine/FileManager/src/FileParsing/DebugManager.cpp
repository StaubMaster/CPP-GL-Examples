#include "FileParsing/DebugManager.hpp"

#include <iostream>



DebugManager::LogChange::LogChange(char data) :
	Data(data)
{ }
bool DebugManager::LogChange::operator==(const LogChange & other) const
{
	return (Data == other.Data);
}



DebugManager::LogChange DebugManager::Tabs('\t');
DebugManager::LogChange DebugManager::TabInc('\x0e');	//	Shift In	-->
DebugManager::LogChange DebugManager::TabDec('\x0f');	//	Shift Out	<--
static unsigned int TabsCount = 0;
static std::string TabsString(TabsCount, ' ');



static std::ostream StreamDump(0);
std::ostream * DebugManager::Console = &StreamDump;



void DebugManager::ChangeConsoleToDump()
{
	Console = &StreamDump;
}
void DebugManager::ChangeConsoleToCOut()
{
	Console = &std::cout;
}



std::ostream & operator<<(std::ostream & log, DebugManager::LogChange & type)
{
	if (type == DebugManager::TabInc) { TabsCount += 2; TabsString = std::string(TabsCount, ' '); }
	if (type == DebugManager::TabDec) { TabsCount -= 2; TabsString = std::string(TabsCount, ' '); }
	if (type == DebugManager::Tabs) { log << TabsString; }
	return log;
}





AnsiCode AnsiCode::Clear("\e[m");
AnsiCode AnsiCode::Black("\e[30m");
AnsiCode AnsiCode::Red("\e[31m");
AnsiCode AnsiCode::Green("\e[32m");
AnsiCode AnsiCode::Yellow("\e[33m");
AnsiCode AnsiCode::Blue("\e[34m");
AnsiCode AnsiCode::Magneta("\e[35m");
AnsiCode AnsiCode::Cyan("\e[36m");
AnsiCode AnsiCode::White("\e[37m");

AnsiCode AnsiCode::Debug("\e[35mDebug: ");
AnsiCode AnsiCode::Info("\e[34mInfo: ");
AnsiCode AnsiCode::Warning("\e[33mWarning: ");
AnsiCode AnsiCode::Error("\e[31mError: ");
AnsiCode AnsiCode::Done("\e[m\n");

AnsiCode::AnsiCode(const char * code)
	: Code(code)
{ }
std::ostream & operator<<(std::ostream & log, AnsiCode & code)
{
	log << code.Code;
	return log;
}

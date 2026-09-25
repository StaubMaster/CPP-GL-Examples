#ifndef  DEBUG_MANAGER_HPP
# define DEBUG_MANAGER_HPP

# include <iosfwd>
# include <fstream>
# include <string>

// different Streams

// Debug
// Info
// Warning
// Error

// Enable / Disable
// put Color
//  Ansi Color vs ColorU4

// Tabs ?
// TabsInc and TabsDec dosent change Log, just have a uint that you can ++ or --
// mave a TabArea Object, ++ when constructed, -- destructed

namespace DebugManager
{
	struct LogChange
	{
		char Data;
		LogChange(char data);
		bool operator==(const LogChange & other) const;
	};

	extern LogChange Tabs;
	extern LogChange TabInc;
	extern LogChange TabDec;

	extern std::ostream * Console;

	std::ostream &	DebugConsole();
	std::ostream &	InfoConsole();
	std::ostream &	WarningConsole();
	std::ostream &	ErrorConsole();

	void ChangeConsoleToDump();
	void ChangeConsoleToCOut();
};

std::ostream & operator<<(std::ostream & log, DebugManager::LogChange & type);

struct AnsiCode
{
	const char *	Code;
	AnsiCode(const char * code);

	static AnsiCode		Clear;
	static AnsiCode		Black;
	static AnsiCode		Red;
	static AnsiCode		Green;
	static AnsiCode		Yellow;
	static AnsiCode		Blue;
	static AnsiCode		Magneta;
	static AnsiCode		Cyan;
	static AnsiCode		White;

	static AnsiCode		Debug;
	static AnsiCode		Info;
	static AnsiCode		Warning;
	static AnsiCode		Error;
	static AnsiCode		Done;
};
std::ostream & operator<<(std::ostream & log, AnsiCode & code);

// Progress()
// ProgressDone()
// ProgressSuccess() Succ
// ProgressFailure() Fail
// ProgressStatus(bool) Succ/Fail

#endif
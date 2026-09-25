#ifndef  DEBUG_HPP
# define DEBUG_HPP

# include <iosfwd>
# include <fstream>

class FileInfo;
class DirectoryInfo;

namespace Debug
{
/*
	<< appends to a temporary stringstream
	at the end of Message, append 0x04 (End of Transmission)
	after that, add extra info stuff to Message
		like timestamp and type
	then output Message to file and clear temporary stream
	how to do additional info ?
	just set with functions
	then clear at end of message
*/

/*	Multithreading
	have a seperate stream for each thread
	at beginning to thread, generate a temporary stream for that thread
	do that when we get there
*/

	std::string TimeStamp();
	std::string TimeStampFileName();

	typedef char LogChange;

	extern LogChange Done;

	extern std::ostringstream Log;
	extern std::ofstream LogFile;

	/*
		seperate for LogFile and other stuff
		maybe LogDebug, LogError, LogInfo
		all that stuff from the C# ConsoleLog
		but those include adding stuff to the stream
		how would I do that ?

		Log should also add TimeStamp
		so I need to intercept the output anyway ?

		how to handle MultiLine output
		out Timestamp on first Line
		and Pad rest

		would this be better on a seperate thread ?
		so the handling dosent slow down the main thread ?
	*/
	extern LogChange Tabs;
	extern LogChange TabInc;
	extern LogChange TabDec;
	extern std::ostream & Console;

	/*	TabObject

		right now you have to manually do
		{
			Debug::Console << Debug::TabInc;
			...
			Debug::Console << Debug::TabDec;
		}
		with an Object you coult
		{
			Debug::TabSection tabs;	//	++++ Constructor increases Tabs
			...
		}	//	---- Destructor decreases Tabs
		would also prevent unclosed Tabs from errors
		make them have Names / Types them automatically
		Types:
			++++
			----
			====
	*/

	void NewFileInDir(const DirectoryInfo & dir);
};

std::ostream & operator<<(std::ostream & log, Debug::LogChange & type);

#endif
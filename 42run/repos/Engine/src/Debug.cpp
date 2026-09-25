#include "Debug.hpp"
#include "FileInfo.hpp"
#include "DirectoryInfo.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <vector>



std::string Debug::TimeStamp()
{
	std::time_t now_t = std::time(NULL);
	std::tm * now = std::localtime(&now_t);

	std::stringstream ss;
	ss << std::setfill('0');
	ss << std::setw(4) << ((now -> tm_year) + 1900) << '-';
	ss << std::setw(2) << ((now -> tm_mon) + 1) << '-';
	ss << std::setw(2) << ((now -> tm_mday)) << ' ';
	ss << std::setw(2) << ((now -> tm_hour)) << ':';
	ss << std::setw(2) << ((now -> tm_min)) << ':';
	ss << std::setw(2) << ((now -> tm_sec)) << ' ';

	return ss.str();
}
std::string Debug::TimeStampFileName()
{
	std::time_t now_t = std::time(NULL);
	std::tm * now = std::localtime(&now_t);

	std::stringstream ss;
	ss << std::setfill('0');

	ss << std::setw(4) << ((now -> tm_year) + 1900) << '_';
	ss << std::setw(2) << ((now -> tm_mon) + 1) << '_';
	ss << std::setw(2) << ((now -> tm_mday)) << '_';
	ss << std::setw(2) << ((now -> tm_hour)) << '_';
	ss << std::setw(2) << ((now -> tm_min)) << '_';
	ss << std::setw(2) << ((now -> tm_sec));

	return ss.str();
}



Debug::LogChange Debug::Done = '\x04';	//	End of Transmission
std::ostringstream Debug::Log;
std::ofstream Debug::LogFile;

Debug::LogChange Debug::Tabs = '\t';		//	does this interfere with regular '\t' ? it shouldn't since the Types are different
Debug::LogChange Debug::TabInc = '\x0e';	//	Shift In	-->
Debug::LogChange Debug::TabDec = '\x0f';	//	Shift Out	<--
static unsigned int TabsCount = 0;
static std::string TabsString(TabsCount, ' ');
std::ostream & Debug::Console = std::cout;



void Debug::NewFileInDir(const DirectoryInfo & dir)
{
	if (Debug::LogFile.is_open())
	{
		Debug::LogFile.close();
	}
	Debug::Log = std::ostringstream();

	FileInfo file(dir.File((TimeStampFileName() + ".log").c_str()));

	Debug::LogFile.open(file.Path.ToString(), std::ofstream::out | std::ofstream::trunc); //std::ofstream::app ?
	Debug::LogFile << "New Log File " << TimeStamp() << "\n";
}



std::ostream & operator<<(std::ostream & log, Debug::LogChange & type)
{
	if (type == Debug::Done)
	{
		std::string timestamp = Debug::TimeStamp();

		std::vector<std::string> lines;
		{
			std::stringstream ss(Debug::Log.str());
			std::string line;
			while (std::getline(ss, line, '\n'))
			{
				lines.push_back(line);
			}
		}
		Debug::Log = std::ostringstream();

		std::string padding = std::string(timestamp.length(), ' ');
		for (size_t i = 0; i < lines.size(); i++)
		{
			if (i == 0)
			{ Debug::LogFile << timestamp; }
			else
			{ Debug::LogFile << padding; }
			Debug::LogFile << lines[i];
			Debug::LogFile << "\n";
		}
		Debug::LogFile.flush();
		return Debug::Log;
	}
	if (type == Debug::TabInc) { TabsCount += 2; TabsString = std::string(TabsCount, ' '); }
	if (type == Debug::TabDec) { TabsCount -= 2; TabsString = std::string(TabsCount, ' '); }
	if (type == Debug::Tabs) { log << TabsString; }
	return log;
}

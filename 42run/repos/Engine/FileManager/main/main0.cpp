#include "FileInfo.hpp"
#include "FileParsing/LineCommand.hpp"
#include "FileParsing/StringHelp.hpp"
#include "FilePath.hpp"
#include "FileParsing/FileParsingCommand.hpp"

struct Test
{
	void TestFunc(const LineCommand & cmd)
	{
		std::cout << "Name: '" << cmd.Name << "'\n";
	}
};

void TestLineCommands()
{
	std::cout << "\n";

	//	Stuff	# comment
	//	Stuff
	//	Stuff	#                    comment

	Test obj;
	LineCommand::Split(FileInfo("main.cpp"), obj, &Test::TestFunc);

	std::cout << "\n";
}

void TestRemoveAll()
{
	std::cout << "\n";

	std::string str0 = "#asd|123#|qwe#asd";
	std::string str1 = "asd123qweasd";
	std::string str2 = StringHelp::RemoveFromString(str0, StringHelp::CharPallet("#|"));

	std::cout << "Have  : " << "'" << str0 << "'\n";
	std::cout << "Want  : " << "'" << str1 << "'\n";
	std::cout << "Result: " << "'" << str2 << "'\n";

	std::cout << "\n";
}

void TestRemovePair(std::string have, std::string want, StringHelp::CharPallet pallet0, StringHelp::CharPallet pallet1)
{
	std::cout << "\n";

	std::string result = StringHelp::RemoveFromString(have, pallet0, pallet1);

	std::cout << "Have  : " << "'" << have << "'\n";
	std::cout << "Want  : " << "'" << want << "'\n";
	std::cout << "Result: " << "'" << result << "'\n";

	std::cout << "\n";
}
void TestRemovePair()
{
	std::cout << "\n";

	StringHelp::CharPallet pallet0("<");
	StringHelp::CharPallet pallet1(">");

	TestRemovePair("asd<123>asd<123>asd", "asdasdasd", pallet0, pallet1);
	TestRemovePair("<123>asd<123>", "asd", pallet0, pallet1);
	TestRemovePair("asd<123>asd<123", "asdasd", pallet0, pallet1);
	TestRemovePair("asd", "asd", pallet0, pallet1);

	std::cout << "\n";
}

struct TestFileParsingCommandEnvironmentData : public FileParsingCommand::EnvironmentData
{
	TestFileParsingCommandEnvironmentData(const FileInfo & file) :
		FileParsingCommand::EnvironmentData(file)
	{ }
	void Parse(const FileParsingCommand & cmd) override
	{
		std::cout << "Cmd: " << cmd << "\n";
	}
};
void TestFileParsingCommand()
{
	{
		FileParsingCommand cmd("test asd 123 321");
		std::cout << "Name: " << cmd.Name() << "\n";
		std::cout << "Count: " << cmd.Count() << "\n";
		std::cout << "cmd: " << cmd << "\n";
		std::cout << "Check: " << cmd.CheckCount(CountCheckEqual(3)) << "\n";
		std::cout << "Check: " << cmd.CheckCount(CountCheckEqual(4)) << "\n";
		std::cout << "Check: " << cmd.CheckCount(CountCheckRange(0, 1)) << "\n";
		std::cout << "Check: " << cmd.CheckCount(CountCheckRange(0, 8)) << "\n";
		std::cout << "Check: " << cmd.CheckCount(CountCheckRange(5, 8)) << "\n";
		std::cout << "Check: " << cmd.CheckCount(CountCheckModulo(2, 1)) << "\n";

		try { throw FileParsingCommand::ExceptionUnknownName(cmd); }
		catch (const std::exception & ex) { std::cerr << ':' << ex.what() << '\n'; }

		try { throw FileParsingCommand::ExceptionInvalidArg(cmd, 2); }
		catch (const std::exception & ex) { std::cerr << ':' << ex.what() << '\n'; }
		try { throw FileParsingCommand::ExceptionInvalidArg(cmd, 3); }
		catch (const std::exception & ex) { std::cerr << ':' << ex.what() << '\n'; }

		try { throw FileParsingCommand::ExceptionInvalidCount(cmd, CountCheckEqual(4)); }
		catch (const std::exception & ex) { std::cerr << ':' << ex.what() << '\n'; }
		try { throw FileParsingCommand::ExceptionInvalidCount(cmd, CountCheckRange(2, 4)); }
		catch (const std::exception & ex) { std::cerr << ':' << ex.what() << '\n'; }
		try { throw FileParsingCommand::ExceptionInvalidCount(cmd, CountCheckModulo(2, 1)); }
		catch (const std::exception & ex) { std::cerr << ':' << ex.what() << '\n'; }
	}

	{
		FileInfo file("test/FileParsingCommand.test.txt");
		TestFileParsingCommandEnvironmentData data(file);
		FileParsingCommand::SplitFileIntoCommands(data);
	}

	{
		FileParsingCommand cmd("test 123 0,67 1.23");
		std::cout << cmd.ToFloat(0) << "\n";
		std::cout << cmd.ToFloat(1) << "\n";
		std::cout << cmd.ToFloat(2) << "\n";
	}
}

int main()
{
	//TestLineCommands();
	//TestRemoveAll();
	//TestRemovePair();
	//FilePath path("test/test\\test");
	//std::cout << path.Segments.size() << "\n";
	TestFileParsingCommand();
	return 0;
}

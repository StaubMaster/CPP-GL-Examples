#ifndef  SCENE_PARSING_HPP
# define SCENE_PARSING_HPP

# include "FileInfo.hpp"
# include "FileParsing/Variables/Float.hpp"

# include "PolyHedra/Manager.hpp"

# include "Miscellaneous/Container/Binary.hpp"
# include "Miscellaneous/Function/Pointer.hpp"
# include "SceneObject/SceneObject.hpp"

struct Light3DContext;

class TextCommand; // TextCommandArguments

struct SceneParsingData
{
	struct ParsingCommand // TextCommandFunction
	{
		std::string		Name;
		FunctionPointer<const TextCommand &>	Func;
		//ParsingCommand(std::string name, const FunctionPointer<const TextCommand &> func);
		ParsingCommand(std::string name);
	};

	FileInfo		File;

	Light3DContext &	Context;

	Container::Binary<ParsingCommand*>	Commands;

	PolyHedraPalletManager *					MissingPolyHedra;
	Container::Binary<PolyHedraPalletManager*>	PolyHedras;

	ParsingVariable::FloatMemory	VariableFloats;

	~SceneParsingData();
	SceneParsingData(const FileInfo & file, Light3DContext & context);

	void	Parse(const TextCommand & cmd);

	void	Parse_PolyHedra(const TextCommand & cmd);
	void	Parse_Place(const TextCommand & cmd);

	void	Parse_LightAmbient(const TextCommand & cmd);
	void	Parse_LightDirectionD(const TextCommand & cmd);
	void	Parse_LightSpotT(const TextCommand & cmd);
};

#endif
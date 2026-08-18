#ifndef  SCENE_PARSING_HPP
# define SCENE_PARSING_HPP

# include "FileInfo.hpp"
# include "FileParsing/Variables/Float.hpp"

//# include "PolyHedra/Manager.hpp"

# include "Generics/Container/Binary.hpp"
# include "Generics/Function/Pointer.hpp"
# include "SceneObject/SceneObject.hpp"

struct Light3DContext;

class TextCommandArgs;

namespace NewPolyHedra
{
struct PalletObjectManager;
};

struct SceneParsingData
{
	struct ParsingCommand // TextCommandFunc ?
	{
		std::string		Name;
		FunctionPointer<const TextCommandArgs &>	Func;
		ParsingCommand(std::string name);
	};

	FileInfo		File;

	Light3DContext &	Context;

	Container::Binary<ParsingCommand*>	Commands;

	//PolyHedraPalletManager *						MissingPolyHedra;
	//Container::Binary<PolyHedraPalletManager*>	PolyHedras;

	// these should be Pallets ?
	NewPolyHedra::PalletObjectManager *						MissingPolyHedra;
	Container::Binary<NewPolyHedra::PalletObjectManager*>	PolyHedras;

	ParsingVariable::FloatMemory	VariableFloats;

	~SceneParsingData();
	SceneParsingData(const FileInfo & file, Light3DContext & context);

	void	Parse(const TextCommandArgs & cmd_args);

	void	Parse_Pallet(const TextCommandArgs & cmd_args);
	void	Parse_Place(const TextCommandArgs & cmd_args);

	void	Parse_LightAmbient(const TextCommandArgs & cmd_args);
	void	Parse_LightDirectionD(const TextCommandArgs & cmd_args);
	void	Parse_LightPoint(const TextCommandArgs & cmd_args);
	void	Parse_LightSpotT(const TextCommandArgs & cmd_args);
};

#endif
#ifndef  SCENE_PARSING_HPP
# define SCENE_PARSING_HPP

# include "FileInfo.hpp"
# include "FileParsing/Variables/Float.hpp"

//# include "PolyHedra/Manager.hpp"

# include "Generics/Container/Binary.hpp"
# include "Generics/Function/Pointer.hpp"
# include "SceneObject/SceneObject.hpp"

struct Light3DContext;

class PolyHedraFileCollection;

namespace TextCommand { class Args; };

namespace NewPolyHedra { struct PalletObjectManager; };

struct SceneParsingData
{
	struct ParsingCommand // TextCommandFunc ?
	{
		std::string		Name;
		FunctionPointer<const TextCommand::Args &>	Func;
		ParsingCommand(std::string name);
	};

	FileInfo		File;

	Light3DContext &	Context;

	::PolyHedraFileCollection &		PolyHedraFileCollection;

	Container::Binary<ParsingCommand*>	Commands;

	//PolyHedraPalletManager *						MissingPolyHedra;
	//Container::Binary<PolyHedraPalletManager*>	PolyHedras;

	// these should be Pallets ?
	NewPolyHedra::PalletObjectManager *						MissingPolyHedra;
	Container::Binary<NewPolyHedra::PalletObjectManager*>	PolyHedras;

	ParsingVariable::FloatMemory	VariableFloats;
	void	PutFloat(const TextCommand::Args & cmd_args);
	float	ToFloat(const TextCommand::Args & cmd_args, unsigned int idx) const;

	~SceneParsingData();
	SceneParsingData(const FileInfo & file, Light3DContext & context, ::PolyHedraFileCollection & file_collection);

	void	Parse(const TextCommand::Args & cmd_args);

	void	Parse_Pallet(const TextCommand::Args & cmd_args);
	void	Parse_Place(const TextCommand::Args & cmd_args);

	void	Parse_LightAmbient(const TextCommand::Args & cmd_args);
	void	Parse_LightDirectionD(const TextCommand::Args & cmd_args);
	void	Parse_LightPoint(const TextCommand::Args & cmd_args);
	void	Parse_LightSpotT(const TextCommand::Args & cmd_args);
};

#endif
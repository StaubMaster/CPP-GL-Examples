#ifndef  SCENE_PARSING_HPP
# define SCENE_PARSING_HPP

# include "FileInfo.hpp"
# include "FileParsing/Variables/Float.hpp"

//# include "PolyHedra/Manager.hpp"

# include "Generics/Container/Binary.hpp"
# include "Generics/Function/Pointer.hpp"
# include "SceneObject/SceneObject.hpp"

# include "Special/Basic3D/Display/Object.hpp"
# include "Special/Basic3D/Display/Data.hpp"

struct Light3DContext;

class PolyHedraManager;

namespace TextCommand { class Args; };

struct SceneParsingData
{
	struct ParsingCommand // TextCommandFunc ?
	{
		std::string		Name;
		Function::Pointer<const TextCommand::Args &>	Func;
		ParsingCommand(std::string name);
	};

	FileInfo		File;

	Light3DContext &	Context;

	::PolyHedraManager &	PolyHedraManager;

	Container::Binary<ParsingCommand*>	Commands;

	// these should be Pallets ?
	NewPolyHedra::Basic3D::DisplayObject *							MissingPolyHedra;
	Container::Binary<NewPolyHedra::Basic3D::DisplayObject *>		PolyHedras;

	ParsingVariable::FloatMemory	VariableFloats;
	void	PutFloat(const TextCommand::Args & cmd_args);
	float	ToFloat(const TextCommand::Args & cmd_args, unsigned int idx) const;

	~SceneParsingData();
	SceneParsingData(const FileInfo & file, Light3DContext & context, ::PolyHedraManager & file_collection);

	void	Parse(const TextCommand::Args & cmd_args);

	void	Parse_Pallet(const TextCommand::Args & cmd_args);
	void	Parse_Place(const TextCommand::Args & cmd_args);

	void	Parse_LightAmbient(const TextCommand::Args & cmd_args);
	void	Parse_LightDirectionD(const TextCommand::Args & cmd_args);
	void	Parse_LightPoint(const TextCommand::Args & cmd_args);
	void	Parse_LightSpotT(const TextCommand::Args & cmd_args);
};

#endif
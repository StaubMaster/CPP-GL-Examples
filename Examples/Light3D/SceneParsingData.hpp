#ifndef  SCENE_PARSING_HPP
# define SCENE_PARSING_HPP

# include "FileInfo.hpp"
# include "FileParsing/Variables/Float.hpp"

# include "PolyHedra/Manager.hpp"

# include "Miscellaneous/Container/Binary.hpp"
# include "SceneObject/SceneObject.hpp"

class TextCommand;

struct SceneParsingData
{
	FileInfo		File;

	::PolyHedraManager &				PolyHedraManager;
	Container::Binary<SceneObject*> &	Objects;

	PolyHedraPalletManager *					MissingPolyHedra;
	Container::Binary<PolyHedraPalletManager*>	PolyHedras;

	ParsingVariable::FloatMemory	VariableFloats;

	~SceneParsingData();
	SceneParsingData(const FileInfo & file, ::PolyHedraManager & manager, Container::Binary<SceneObject*> & objects);

	void	Parse(const TextCommand & cmd);

	void	Parse_PolyHedra(const TextCommand & cmd);
	void	Parse_Place(const TextCommand & cmd);
};

#endif
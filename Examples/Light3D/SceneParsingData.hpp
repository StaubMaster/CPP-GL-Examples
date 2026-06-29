#ifndef  SCENE_PARSING_HPP
# define SCENE_PARSING_HPP

# include "FileInfo.hpp"
# include "FileParsing/Variables/Float.hpp"

# include "PolyHedra/Manager.hpp"

# include "Miscellaneous/Container/Binary.hpp"
# include "SceneObject/SceneObject.hpp"

struct Light3DContext;

class TextCommand;

struct SceneParsingData
{
	FileInfo		File;

	Light3DContext &	Context;

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
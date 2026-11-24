#ifndef  SCENE_PARSING_HPP
# define SCENE_PARSING_HPP

# include "FileInfo.hpp"
# include "FileParsing/Variables/Float.hpp"
# include "FileParsing/Variables/Memory.hpp"

# include "FileParsing/TextCommand/Func.hpp"
# include "FileParsing/TextCommand/Loop.hpp"

namespace TextCommand { class Args; };

# include "Generics/Container/Binary.hpp"
# include "Generics/Function/Pointer.hpp"

# include "SceneObject/.hpp"
# include "SceneObject/Manager.hpp"

# include "Special/Basic3D/Display/Object.hpp"
# include "Special/Basic3D/Display/Data.hpp"

struct Light3DContext;

# include <string>

namespace NewPolyHedra { struct Pallet; };

struct SceneParsingData : public TextCommand::Loop
{
	SceneObject_Manager &	Manager;

	Light3DContext &	Context; // use SceneObject_Collection
	/* why is Context needed ?
		NewPolyHedra Managers
		LightManager
	*/
	/* what does .scene File actually give ?
		File of PolyHedra

		store that in SceneObject
		then make actual NewPolyHedra stuff later

		how to do LightManager ?
			take from LightObjects when Displaying
	*/



	VariableMemory		Variables;

	void	PutFloat(const TextCommand::Args & cmd_args);
	float	ToFloat(const TextCommand::Args & cmd_args, unsigned int idx) const;



	SceneParsingData(const FileInfo & file, SceneObject_Manager & manager, Light3DContext & context);



	//void	Parse(const TextCommand::Args & cmd_args);

	void	Parse_Pallet(const TextCommand::Args & cmd_args);
	void	Parse_Place(const TextCommand::Args & cmd_args);

	void	Parse_LightAmbient(const TextCommand::Args & cmd_args);
	void	Parse_LightDirectionD(const TextCommand::Args & cmd_args);
	void	Parse_LightPoint(const TextCommand::Args & cmd_args);
	void	Parse_LightSpotT(const TextCommand::Args & cmd_args);
};

#endif
#include "SceneParsingData.hpp"

#include "FileParsing/Text/Exceptions.hpp"
#include "FileParsing/Text/TextCommand.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
#include "SceneObject/PolyHedraObject.hpp"

#include <iostream>





SceneParsingData::~SceneParsingData()
{ }
SceneParsingData::SceneParsingData(const FileInfo & file, ::PolyHedraManager & manager, Container::Binary<SceneObject*> & objects)
	: File(file)
	, PolyHedraManager(manager)
	, Objects(objects)
	, PolyHedras()
{
	MissingPolyHedra = PolyHedraManager.MakePallet(PolyHedraGenerate::RegularHexaHedron(1.0f));
}

void SceneParsingData::Parse(const TextCommand & cmd)
{
	try
	{
		std::string name = cmd.Name();
		if (name == "") { /*std::cout << "empty\n";*/ }

		else if (name == "varFloat")	{ VariableFloats.Put(cmd); }

		else if (name == "polyhedra")	{ Parse_PolyHedra(cmd); }
		else if (name == "place")		{ Parse_Place(cmd); }

		else { std::cout << "unknown: " << cmd << '\n'; }
	}
	catch (std::exception & ex)
	{
		std::cout << "Exception while Parsing Scene: " << ex.what() << '\n';
		std::cout << "Exception on TextCommand: " << cmd << '\n';
	}
}

void SceneParsingData::Parse_PolyHedra(const TextCommand & cmd)
{
	if (!(cmd.Count() == 1)) { throw InvalidCommandArgumentCount(cmd, "n == 1"); }

	FileInfo file((File.DirectoryString() + "/" + cmd.ToString(0)).c_str());
	if (!file.Exists()) { std::cout << cmd.Name() << ": " << "Bad Skin File" << "\n"; return; }
	PolyHedra * polyhedra = PolyHedra::Load(file);
	//polyhedra -> UseCornerNormals = true;
	PolyHedraPalletManager * manager = PolyHedraManager.MakePallet(polyhedra);
	PolyHedras.Insert(manager);
}
void SceneParsingData::Parse_Place(const TextCommand & cmd)
{
	if (!(cmd.Count() == 7)) { throw InvalidCommandArgumentCount(cmd, "n == 7"); }

	std::string name = cmd.ToString(0);
	PolyHedraPalletManager * polyhedra = MissingPolyHedra;
	for (unsigned int i = 0; i < PolyHedras.Count(); i++)
	{
		if (PolyHedras[i] -> Pallet -> Name == name)
		{
			polyhedra = PolyHedras[i];
		}
	}

	Trans3D trans(
		VectorF3(
			VariableFloats.To(cmd, 1),
			VariableFloats.To(cmd, 2),
			VariableFloats.To(cmd, 3)
		),
		EulerAngle3D::Degrees(
			VariableFloats.To(cmd, 4),
			VariableFloats.To(cmd, 5),
			VariableFloats.To(cmd, 6)
		)
	);

	Objects.Insert(new SceneObject_PolyHedraObject(polyhedra, trans));
}

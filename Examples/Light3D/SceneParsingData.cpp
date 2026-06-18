#include "SceneParsingData.hpp"

#include "FileParsing/Text/Exceptions.hpp"
#include "FileParsing/Text/TextCommand.hpp"

#include "PolyHedra/PolyHedra.hpp"
#include "PolyHedra/Generate.hpp"
#include "SceneObject/PolyHedraObject.hpp"

#include <iostream>



SceneParsingData::MapVariableFloat::Variable * SceneParsingData::MapVariableFloat::Find(std::string name)
{
	for (unsigned int i = 0; i < Variables.Count(); i++)
	{
		if (Variables[i].Name == name)
		{
			return &Variables[i];
		}
	}
	return nullptr;
}
void SceneParsingData::MapVariableFloat::Put(const TextCommand & cmd)
{
	if (!(cmd.Count() == 2)) { throw InvalidCommandArgumentCount(cmd, "n == 2"); }
	Variable * var = Find(cmd.ToString(0));
	if (var != nullptr)
	{
		var -> Value = cmd.ToFloat(1);
	}
	else
	{
		Variable v;
		v.Name = cmd.ToString(0);
		v.Value = cmd.ToFloat(1);
		Variables.Insert(v);
	}
}
float SceneParsingData::MapVariableFloat::To(const TextCommand & cmd, unsigned int idx)
{
	std::string str = cmd.ToString(idx);
	char c = str[0];

	bool s = false;
	s = (c == '+' || c == '-');

	if (s) { c = str[1]; }

	if ((c >= '0' && c <= '9')) { return cmd.ToFloat(idx); }

	if (s) { c = str[0]; str.erase(0, 1); }

	Variable * var = Find(str);
	if (var != nullptr)
	{
		float v = var -> Value;
		if (s)
		{
			if (c == '+') { v = +v; }
			if (c == '-') { v = -v; }
		}
		return v;
	}
	return 0.0f; // return NaN ?
}





SceneParsingData::~SceneParsingData()
{ }
SceneParsingData::SceneParsingData(const FileInfo & file, ::PolyHedraManager & manager, Container::Binary<SceneObject*> & objects)
	: File(file)
	, PolyHedraManager(manager)
	, Objects(objects)
	, PolyHedras()
{
	MissingPolyHedra = PolyHedraManager.MakePallet(PolyHedra::Generate::HexaHedron(1.0f));
}

void SceneParsingData::Parse(const TextCommand & cmd)
{
	try
	{
		std::string name = cmd.Name();
		if (name == "") { /*std::cout << "empty\n";*/ }

		else if (name == "varFloat")	{ VarsFloat.Put(cmd); }

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
	PolyHedras.Insert(PolyHedraManager.MakePallet(PolyHedra::Load(file)));
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
			VarsFloat.To(cmd, 1),
			VarsFloat.To(cmd, 2),
			VarsFloat.To(cmd, 3)
		),
		EulerAngle3D::Degrees(
			VarsFloat.To(cmd, 4),
			VarsFloat.To(cmd, 5),
			VarsFloat.To(cmd, 6)
		)
	);

	Objects.Insert(new SceneObject_PolyHedraObject(polyhedra, trans));
}

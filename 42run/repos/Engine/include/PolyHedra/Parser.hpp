#ifndef  POLYHEDRA_PARSING_HPP
# define POLYHEDRA_PARSING_HPP

# include "PolyHedra/PolyHedra.hpp"

# include "FileInfo.hpp"
# include "FileParsing/Variables/Float.hpp"

# include "FileParsing/TextCommand/Func.hpp"
# include "FileParsing/TextCommand/Loop.hpp"

# include "Generics/Container/Binary.hpp"
# include "Generics/Function/Pointer.hpp"
# include "Generics/Function/Object.hpp"

# include "ValueType/Trans/3D.hpp"

# include <string>

namespace TextCommand { class Args; };

struct PolyHedraParser : public TextCommand::Loop
{
	struct CommandFlags
	{
		bool	Direction = false;
		bool	Closed = true;
		bool	Middle = false;
		void	MakeDefault();

		~CommandFlags() = default;
		CommandFlags() = default;
		CommandFlags(const CommandFlags & other) = default;
		CommandFlags & operator=(const CommandFlags & other) = default;

		bool			Parse(char c);
		unsigned int	Parse(const std::string & name);
	};
	CommandFlags	DefaultFlags;
	struct CommandFlagsFunc : public TextCommand::Func
	{
		FunctionPointer<const TextCommand::Args &, const CommandFlags &>		Function;

		~CommandFlagsFunc();
		template<typename ObjectType> CommandFlagsFunc(
			std::string name,
			ObjectType * obj,
			void (ObjectType::*func)(const TextCommand::Args &, const CommandFlags &)
		)
			: Func(name)
			, Function(obj, func)
		{ }
	
		bool	TryInvoke(const TextCommand::Args & cmd_args) const override;
	};
	// each Command takes different Flags

	void	CommandsDefault();
	void	CommandsNormal();
	void	CommandsLegacy();



	ParsingVariable::FloatMemory	VariableFloats;
	void	PutVariable(const TextCommand::Args & cmd_args);
	void	PutFloat(const TextCommand::Args & cmd_args);
	float	ToFloat(std::string str) const;
	float	ToFloat(const TextCommand::Args & cmd_args, unsigned int idx) const;



	public:
	PolyHedra *		Object = nullptr;

	unsigned int	NormalGroup = 0xFFFFFFFF;

	const PolyHedraParser *		Parser = nullptr;

	PolyHedraFileCollection *	FileCollection = nullptr;

	Trans3D		Trans;

	const PolyHedra *	Other = nullptr;

	unsigned int	VertexOffset;
	unsigned int	ToVertexIndex(const TextCommand::Args & cmd_args, unsigned int arg_idx) const;



	~PolyHedraParser();
	PolyHedraParser(const PolyHedraParser * parser, PolyHedraFileCollection * file_collection);



	void	Check_Type(const TextCommand::Args & cmd_args);
	void	Change_Format(const TextCommand::Args & cmd_args);

	void	Check_Parameter(const TextCommand::Args & cmd_args);

	void	New_Skin(const TextCommand::Args & cmd_args);

	void	Change_Default(const TextCommand::Args & cmd_args);
	void	Change_Offset(const TextCommand::Args & cmd_args);

	void	Legacy_Face3(const TextCommand::Args & cmd_args);
	void	Legacy_Face4(const TextCommand::Args & cmd_args);
	void	Legacy_Face34(const TextCommand::Args & cmd_args);
	void	Legacy_Offset2(const TextCommand::Args & cmd_args);

	void	Place_Vertex(const TextCommand::Args & cmd_args);
	void	Place_Circle(const TextCommand::Args & cmd_args, const CommandFlags & flags);

	void	Place_Face(const TextCommand::Args & cmd_args, const CommandFlags & flags);
	void	Place_Belt(const TextCommand::Args & cmd_args, const CommandFlags & flags);
	void	Place_Band(const TextCommand::Args & cmd_args, const CommandFlags & flags);
	void	Place_Fan(const TextCommand::Args & cmd_args, const CommandFlags & flags);

	void	Normal_Change(const TextCommand::Args & cmd_args);

	void	Trans_Zero(const TextCommand::Args & cmd_args);
	void	Trans_ChangePos(const TextCommand::Args & cmd_args);
	void	Trans_ChangeRot(const TextCommand::Args & cmd_args);

	void	Other_File(const TextCommand::Args & cmd_args);
	void	Other_Static(const TextCommand::Args & cmd_args);
	void	Other_Dynamic(const TextCommand::Args & cmd_args);



	static PolyHedra * Load(const FileInfo & file, const PolyHedraParser * parser, PolyHedraFileCollection * file_collection);
};

#endif

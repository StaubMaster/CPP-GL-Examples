#ifndef  SKIN_PARSING_HPP
# define SKIN_PARSING_HPP

# include "Skin.hpp"

namespace TextCommand { class Args; };

struct Skin::ParsingData
{
	const FileInfo &	File;
	::Skin &			Skin;

	unsigned int	TextureIndex;
	unsigned int	TextureVertexIndex;

	unsigned int	ToVertexIndex(const TextCommand::Args & cmd_args, unsigned int arg_idx) const;

	~ParsingData();
	ParsingData(const FileInfo & file, ::Skin & skin);



	void	Parse(const TextCommand::Args & cmd_args);
	void	Parse_Type(const TextCommand::Args & cmd_args);
	void	Parse_Format(const TextCommand::Args & cmd_args);

	void	Parse_Name(const TextCommand::Args & cmd_args);
	void	Parse_Size(const TextCommand::Args & cmd_args);
	void	Parse_Image(const TextCommand::Args & cmd_args);

	void	Parse_t(const TextCommand::Args & cmd_args);

	void	Parse_TextureIndex(const TextCommand::Args & cmd_args);
	void	Parse_TextureIndexFace4(const TextCommand::Args & cmd_args);
	void	Parse_TextureIndexQuad(const TextCommand::Args & cmd_args);

	void	Parse_Vertex(const TextCommand::Args & cmd_args);			// VertexCoord()
	void	Parse_VertexIndex(const TextCommand::Args & cmd_args);	// VertexOffset()

	void	Parse_VertexFace3(const TextCommand::Args & cmd_args, bool f_direction);
	void	Parse_VertexBelt(const TextCommand::Args & cmd_args, bool f_direction, bool f_closure);
	void	Parse_VertexBand(const TextCommand::Args & cmd_args, bool f_direction, bool f_closure);
	void	Parse_VertexFan(const TextCommand::Args & cmd_args, bool f_direction, bool f_closure, bool f_middle);

	void	Parse_VertexRay(const TextCommand::Args & cmd_args, bool f_accumulate);

	void	Parse_ColorF_Default(const TextCommand::Args & cmd_args);
	void	Parse_ColorF(const TextCommand::Args & cmd_args);

	void	Parse_ColorD_Default(const TextCommand::Args & cmd_args);
	void	Parse_ColorD(const TextCommand::Args & cmd_args);

	void	Parse_Multi(const TextCommand::Args & cmd_args);
};

#endif

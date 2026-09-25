#ifndef  WAVEFRONT_OBJ_HPP
# define WAVEFRONT_OBJ_HPP

# include "MTL.hpp"

# include "DataDeclare.hpp"
# include "Display/SizeRatio2D.hpp"

# include "Generics/Container/Binary.hpp"

# include <exception>



class LineCommand;
class FileInfo;

//class MTL;

namespace Wavefront
{
namespace Main
{
struct Data;
};
class OBJ
{
	private:
	class FaceCorner
	{
		public:
			unsigned int Position;
			unsigned int Texture;
			unsigned int Normal;
		public:
			FaceCorner();
	};
	class Face
	{
		public:
			FaceCorner Corner1;
			FaceCorner Corner2;
			FaceCorner Corner3;
			unsigned int MaterialIndex;
		public:
			Face();
	};

	private:
	std::string Path;

	Container::Binary<VectorF4> Positions;
	Container::Binary<VectorF3> Textures;
	Container::Binary<VectorF3> Normals;
	Container::Binary<Face> Faces;

	MTL Materials;

	private:
	OBJ();
	public:
	~OBJ();

	public:
	VectorF4 Position_MainData(unsigned int idx);
	VectorF3 Texture_MainData(unsigned int idx, VectorF4 pos, SizeRatio2D scale, char sides);
	VectorF3 Normal_MainData(unsigned int idx, VectorF3 normal);
	Main::Data * ToMainData(int & count, SizeRatio2D texScale);

	private:
	void Parse_v(const LineCommand & cmd);
	void Parse_vt(const LineCommand & cmd);
	void Parse_vn(const LineCommand & cmd);

	FaceCorner Parse_f_element(std::string text);
	void Parse_f(const LineCommand & cmd);

	void Parse_o(const LineCommand & cmd);
	void Parse_s(const LineCommand & cmd);

	void Parse_mtllib(const LineCommand & cmd);
	void Parse_usemtl(const LineCommand & cmd);

	void Parse(const LineCommand & cmd);

	public:
	static OBJ * Load(const FileInfo & file);

	public:
	BoxF3 ToAxisBox();

	private:
	class Exception_InvalidString : public std::exception
	{
		private:
			std::string Line;
			std::string Text;
		public:
			Exception_InvalidString(std::string line, std::string text);
		public:
			const char * what() const noexcept;
	};
};
};

#endif
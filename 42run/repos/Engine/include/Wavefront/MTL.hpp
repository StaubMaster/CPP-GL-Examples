#ifndef  WAVEFRONT_MTL_HPP
# define WAVEFRONT_MTL_HPP

# include "ValueType/Color/U4.hpp"

# include "Generics/Container/Binary.hpp"

# include <exception>
# include <iostream>



class LineCommand;
class FileInfo;

namespace Wavefront
{
class MTL
{
	public:
		class Material
		{
			public:
				std::string Name;
				ColorF4	Ka;	//	ambient
				ColorF4	Kd;	//	diffuse
				ColorF4	Ks;	//	specular
				float	Ns;	//	specular
				float	Ni;	//	"optical density"
				float	d;	//	"dissolve"
				float	Tr;	//	Transparent = 1.0 - d;
				int		illum;	//	look it up idiot
			public:
				Material();
			public:
				std::string ToString();
		};

	public:
		Container::Binary<Material> Materials;
		Material DefaultMaterial;

	private:
		unsigned int Index_Newest;
	public:
		unsigned int Index_Selected;

	public:
		MTL();
		~MTL();

	public:
		Material * Newest();
		Material & Index(unsigned int idx);
	public:
		void Insert(MTL & mtl);
		void Select(std::string name);

	private:
		void Parse_newmtl(const LineCommand & cmd);
		void Parse_Ka(const LineCommand & cmd);
		void Parse_Kd(const LineCommand & cmd);
		void Parse_Ks(const LineCommand & cmd);
		void Parse_Ns(const LineCommand & cmd);
		void Parse_Ni(const LineCommand & cmd);
		void Parse_d(const LineCommand & cmd);
		void Parse_illum(const LineCommand & cmd);
		void Parse(const LineCommand & cmd);

	public:
		static MTL * Load(const FileInfo & file);
};
};

#endif
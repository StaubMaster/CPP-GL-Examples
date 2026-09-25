#ifndef  PARSING_VARIABLE_FLOAT_HPP
# define PARSING_VARIABLE_FLOAT_HPP

# include <string>

# include "Generics/Container/Binary.hpp"

namespace ParsingVariable
{
	struct Float
	{
		std::string		Name;
		float			Value;

		~Float() = default;
		Float() = default;
		Float(const Float & other) = default;
		Float & operator=(const Float & other) = default;

		Float(std::string name, float value);

		static bool		IsLiteral(std::string str);
		static float	ParseLiteral(std::string str);

		static char		SignTake(std::string & str);
		static float	SignPut(float value, char sign);
	};

	struct FloatMemory
	{
		Container::Binary<Float>	Variables;

		~FloatMemory() = default;
		FloatMemory() = default;
		FloatMemory(const FloatMemory & other) = default;
		FloatMemory & operator=(const FloatMemory & other) = default;

				Float *		Find(std::string name);
		const	Float *		Find(std::string name) const;

		void	Put(std::string name, float value);
		float	To(std::string str) const;
	};
};

#endif
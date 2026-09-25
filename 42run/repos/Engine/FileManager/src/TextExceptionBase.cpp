#include "TextExceptionBase.hpp"



TextExceptionBase::TextExceptionBase()
{ }
const char * TextExceptionBase::what() const noexcept
{
	return Text.c_str();
}

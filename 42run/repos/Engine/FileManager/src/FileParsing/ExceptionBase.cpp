#include "FileParsing/ExceptionBase.hpp"



ExceptionBase::ExceptionBase()
{

}

const char * ExceptionBase::what() const noexcept
{
	return Text.c_str();
}

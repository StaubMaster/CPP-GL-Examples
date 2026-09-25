#include "FileParsing/BitStreamBase.hpp"



BitStreamBase::~BitStreamBase() { }

BitStreamBase::BitStreamBase(ByteBlock block)
	: Block(block)
{ }

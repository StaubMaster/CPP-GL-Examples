#include "FileParsing/ByteStreamBase.hpp"



ByteStreamBase::~ByteStreamBase() { }



ByteStreamBase::ByteStreamBase(ByteBlock block)
	: Block(block)
	, Order(ByteOrder::HiToLo)
{ }

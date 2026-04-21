#include "ContextBase.hpp"



ContextBase::~ContextBase() { }
ContextBase::ContextBase(::Window & window)
	: window(window)
	, MediaDirectory("../../media/")
{ }

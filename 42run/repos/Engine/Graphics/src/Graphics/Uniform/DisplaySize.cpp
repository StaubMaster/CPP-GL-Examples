#include "Graphics/Uniform/DisplaySize.hpp"
#include "Display/DisplaySize.hpp"



Uniform::DisplaySize::DisplaySize(std::string name, bool is_dynamic)
	: TypeBase(name, is_dynamic)
	, Ratio(Name + ".Ratio")
	, Window(Name + ".Window")
	, Buffer(Name + ".Buffer")
{ }
Uniform::DisplaySize::DisplaySize(Uniform::Layout & layout, std::string name, bool is_dynamic)
	: TypeBase(layout, name, is_dynamic)
	, Ratio(layout, Name + ".Ratio")
	, Window(layout, Name + ".Window")
	, Buffer(layout, Name + ".Buffer")
{ }



void Uniform::DisplaySize::Put(const ::DisplaySize & obj)
{
	Ratio.Put(obj.Ratio);
	Window.Put(obj.Window);
	Buffer.Put(obj.Buffer);
}

#include "NodePath.hpp"



const Trans3D & NodePath::First() const { return Nodes[0]; }
const Trans3D & NodePath::Last() const { return Nodes[Nodes.Count() - 1]; }

void NodePath::NewNode(const Trans3D & trans)
{
	unsigned int i = Nodes.Count();
	Nodes.Insert(trans);
	if (i != 0)
	{
		float len = (Nodes[i - 1].Position - Nodes[i - 0].Position).length();
		Lengths.Insert(len);
		LengthSum += len;
	}
}

/*void NodePath::New(unsigned int count)
{
	Nodes.NewLength(count);
	Lengths.NewLength((count != 0) ? (count - 1) : 0);
}*/

/*void NodePath::CalculateLengths()
{
	LengthSum = 0.0f;
	for (unsigned int i = 0; i < Lengths.Length(); i++)
	{
		Lengths[i] = (Nodes[i + 0].Position - Nodes[i + 1].Position).length();
		LengthSum += Lengths[i];
	}
	LengthLimit = LengthSum;
}*/

bool NodePath::Interpolate(float & t, Trans3D & node0, Trans3D & node1) const
{
	for (unsigned int i = 0; i < Lengths.Count(); i++)
	{
		if (t < Lengths[i])
		{
			t = t / Lengths[i];
			node0 = Nodes[i + 0];
			node1 = Nodes[i + 1];
			return true;
		}
		t -= Lengths[i];
	}
	return false;
}



NewPolyHedra::Basic3D::PalletObjectManager * NodePath::Object = nullptr;

void NodePath::Display(const Trans3D & trans) const
{
	NewPolyHedra::Basic3D::ObjectData data;
	for (unsigned int i = 0; i < Nodes.Count(); i++)
	{
		data.Trans = trans.forward(Nodes[i]);
		Object -> InstancesFullPut(data);
	}
}

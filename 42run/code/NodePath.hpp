#ifndef  NODE_PATH_HPP
# define NODE_PATH_HPP

# include "ValueType/Trans/3D.hpp"
# include "Generics/Container/Binary.hpp"

# include "NewPolyHedra/DataType/Basic3D/PalletObjectManager.hpp"

struct NodePath
{
	// Binary ? calculate Lengths dynamically

	Container::Binary<Trans3D>	Nodes;
	Container::Binary<float>	Lengths;
	float						LengthSum = 0.0f;
	float						LengthLimit = 0.0f;

	const Trans3D &		First() const;
	const Trans3D &		Last() const;

	~NodePath() = default;
	NodePath() = default;
	NodePath(const NodePath & other) = default;
	NodePath & operator=(const NodePath & other) = default;

	void	NewNode(const Trans3D & trans);

	bool	Interpolate(float & t, Trans3D & node0, Trans3D & node1) const;



	static NewPolyHedra::Basic3D::PalletObjectManager *		Object;

	void	Display(const Trans3D & trans) const;
};

#endif
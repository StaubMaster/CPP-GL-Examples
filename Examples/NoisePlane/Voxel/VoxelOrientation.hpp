#ifndef  VOXEL_ORIENTATION_HPP
# define VOXEL_ORIENTATION_HPP

# include "VoxelEnums.hpp"
# include "ValueType/VectorF3.hpp"

struct VoxelOrientation
{
	private:
	unsigned char Value;
	public:

	Diag	GetDiag() const;
	Flip	GetFlip() const;

	void	SetDiag(Diag diag);
	void	SetFlip(Flip flip);

	~VoxelOrientation();
	VoxelOrientation();

	VoxelOrientation(const VoxelOrientation & other);
	VoxelOrientation & operator=(const VoxelOrientation & other);

	void	make(Diag diag, Flip flip);
	void	make(Axis origin, Axis target);
	void	make(Axis origin0, Axis target0, Axis origin1, Axis target1); // make this a static function ?

	VectorF3	absolute(VectorF3 v) const;
	Axis		absolute(Axis axis) const;
	Axis		relative(Axis axis) const;
};

#endif
#ifndef  VOXEL_PALLET_GEOMETRY_PARSER_HPP
# define VOXEL_PALLET_GEOMETRY_PARSER_HPP

/* another on of these

File contains an arbitrary number of Geometrys
Geometrys are put into Map
each Name only once, show Error if problems, keep loading

Map can be made from multiple Files
give Map to Parser


Name "name"		# starts a new Geometry
done			# ends a Geometry
				# end automatically at end of File or if next begins

# only the U Corners are allowed, no need to specify ?
# DataU only has 1 Quad Face per side

# DataU.PrevX.Quad0(pos[0b000], pos[0b010], pos[0b100], pos[0b110], BoxU2(VectorU2(0, 0), VectorU2(1, 1)), 0);
quad0   prevX   000 010 100 110   0.0 0.0 1.0 1.0   0

*/

#endif
#ifndef  CHUNK_GENERATION_NOISE_HPP
# define CHUNK_GENERATION_NOISE_HPP

# include "ValueGen/Perlin2D.hpp"
# include "ValueGen/Perlin3D.hpp"

struct ChunkGenerationNoise
{
	Perlin2D	Plane;
	Perlin3D	Cave0;
	Perlin3D	Cave1;
	Perlin3D	Cave2;
};

#endif
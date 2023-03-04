#include "buildTerrainMesh.h"

using namespace glm;

void buildTerrainMesh(ofMesh& terrainMesh, const ofShortPixels& heightmap, unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd, vec3 scale)
{
	for (unsigned int y { yStart }; y < yEnd; ++y)
	{
		for (unsigned int x { xStart }; x < xEnd; ++x)
		{
			if (heightmap.getColor(x, y).r > 0 && heightmap.getColor(x, y).r < USHRT_MAX)
			{
				const float h { heightmap.getColor(x, y).r / static_cast<float>(0xffff) };	// USHRT_MAX = 0xffff
				terrainMesh.addVertex(vec3(x, h, y) * scale);
				terrainMesh.addColor(ofFloatColor(1, 0, 0));
			}
			
		}
	}

	for (unsigned int y { yStart }; y < yEnd - 1; ++y)
	{
		for (unsigned int x { xStart }; x < xEnd - 1; ++x)
		{
			terrainMesh.addIndex(x + y * yEnd);
			terrainMesh.addIndex(x + (y + 1) * yEnd);
			terrainMesh.addIndex((x + 1) + y * yEnd);

			terrainMesh.addIndex((x + 1) + y * yEnd);
			terrainMesh.addIndex(x + (y + 1) * yEnd);
			terrainMesh.addIndex((x + 1) + (y + 1) * yEnd);
		}
	}
}
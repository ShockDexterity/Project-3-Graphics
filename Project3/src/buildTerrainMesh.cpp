#include "buildTerrainMesh.h"

using namespace glm;

void buildTerrainMesh(ofMesh& terrainMesh, const ofShortPixels& heightmap, unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd, vec3 scale)
{
	for (unsigned int y { yStart }; y <= yEnd; ++y)
	{
		for (unsigned int x { xStart }; x <= xEnd; ++x)
		{
			if (heightmap.getColor(x, y).r > 0 && heightmap.getColor(x, y).r < USHRT_MAX)
			{
				const float h { heightmap.getColor(x, y).r / static_cast<float>(USHRT_MAX) };	// USHRT_MAX = 0xffff
				terrainMesh.addVertex(vec3(x, h, y) * scale);
			}
		}
	}

	for (unsigned int y { yStart }; y < yEnd; ++y)
	{
		for (unsigned int x { xStart }; x < xEnd; ++x)
		{
			unsigned int i1 { x + y * xEnd };
			unsigned int i2 { x + (y + 1) * xEnd + 1 };
			unsigned int i3 { (x + 1) + y * xEnd };
			unsigned int i4 { (x + 1) + y * xEnd };
			unsigned int i5 { x + (y + 1) * xEnd + 1 };
			unsigned int i6 { (x + 1) + (y + 1) * xEnd + 1 };

			terrainMesh.addIndex(i1 + y);
			terrainMesh.addIndex(i2 + y);
			terrainMesh.addIndex(i3 + y);
			terrainMesh.addIndex(i4 + y);
			terrainMesh.addIndex(i5 + y);
			terrainMesh.addIndex(i6 + y);
		}
	}
}
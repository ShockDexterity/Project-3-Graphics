#include "buildTerrainMesh.h"

using namespace glm;

void buildTerrainMesh(ofMesh& terrainMesh, const ofShortPixels& heightmap, unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd, vec3 scale)
{
	for (unsigned int y { yStart }; y < yEnd; ++y)
	{
		for (unsigned int x { xStart }; x < xEnd; ++x)
		{
			const auto h { heightmap.getColor(x, y).r };
			terrainMesh.addVertex(vec3(x, h / static_cast<float>(0xffff), y) * scale); // USHRT_MAX = 0xffff
			terrainMesh.addColor(ofFloatColor(1, 0, 0));
		}
	}

	for (unsigned int y { 0 }; y < yEnd - 1; ++y)
	{
		for (unsigned int x { 0 }; x < xEnd - 1; ++x)
		{
			terrainMesh.addIndex(x + y * yEnd);
			terrainMesh.addIndex(x + (y + 1) * yEnd);
			terrainMesh.addIndex((x + 1) + y * yEnd);

			terrainMesh.addIndex(x + (y + 1) * yEnd);
			terrainMesh.addIndex((x + 1) + (y + 1) * yEnd);
			terrainMesh.addIndex((x + 1) + y * yEnd);
		}
	}
}
#include "buildTerrainMesh.h"

using namespace glm;

void buildTerrainMesh(ofMesh& terrainMesh, const ofShortPixels& heightmap, unsigned int xStart, unsigned int yStart, unsigned int xEnd, unsigned int yEnd, vec3 scale)
{
	cout << xEnd << ' ' << yEnd << '\n';
	for (unsigned int y { yStart }; y <= yEnd; ++y)
	{
		for (unsigned int x { xStart }; x <= xEnd; ++x)
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
			unsigned int i1 { x + y * xEnd };
			unsigned int i2 { x + (y + 1) * xEnd + 1 };
			unsigned int i3 { (x + 1) + y * xEnd };
			unsigned int i4 { (x + 1) + y * xEnd };
			unsigned int i5 { x + (y + 1) * xEnd + 1 };
			unsigned int i6 { (x + 1) + (y + 1) * xEnd + 1 };

			if (y != 0)
			{
				++i1;
				++i2;
				++i3;
				++i4;
				++i5;
				++i6;
			}

			terrainMesh.addIndex(i1);
			terrainMesh.addIndex(i2);
			terrainMesh.addIndex(i3);
			terrainMesh.addIndex(i4);
			terrainMesh.addIndex(i5);
			terrainMesh.addIndex(i6);

			std::vector<unsigned int> vec { i1,i2,i3,i4,i5,i6 };

			if (true)
			{
				std::cout << "{ ";
				for (unsigned int i : vec)
				{
					std::cout << i << ' ';
				}
				std::cout << '}' << '\n';
			}
		}
	}
}
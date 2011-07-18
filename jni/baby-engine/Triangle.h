#pragma once

#include "Mesh.h"

class Triangle : public Mesh {

private:

	float getPart(float x1, float x2, float part) {
		return x1 + (x2 - x1) * part;
	}

	void init(float size, int segmentsByDimension) {
		init(segmentsByDimension, 
				Vec3f(0, (float)(size / sqrt(3)), 0),
				Vec3f(-size/2, (float)(-size/(2 * sqrt(3))), 0), 
				Vec3f(size/2, (float)(-size/(2 * sqrt(3))), 0));
	}

	void init(int segmentsByDimension, Vec3f point1, Vec3f point2, Vec3f point3) {
		int verticesCount = (segmentsByDimension + 1) * (segmentsByDimension + 2) / 2;
		Vec3f *vertices = new Vec3f[verticesCount];
		int indicesCount = segmentsByDimension * segmentsByDimension * 3;
		unsigned short *indices = new unsigned short[indicesCount];
		
		int vCounter = 0;
		int iCounter = 0;
		Vec3f leftPoint, rightPoint;
		for (int j = 0; j <= segmentsByDimension; j++) {
			float part = (float)j / segmentsByDimension;
			leftPoint.Set(
				getPart(point1.x, point2.x, part),
				getPart(point1.y, point2.y, part),
				getPart(point1.z, point2.z, part));
			rightPoint.Set(
				getPart(point1.x, point3.x, part),
				getPart(point1.y, point3.y, part),
				getPart(point1.z, point3.z, part));
			for (int i = 0; i <= j; i++) {
				float part2 = j == 0 ? 0 : ((float)i / j);
				vertices[vCounter].Set(
					getPart(leftPoint.x, rightPoint.x, part2), 
					getPart(leftPoint.y, rightPoint.y, part2),
					getPart(leftPoint.z, rightPoint.z, part2));
				vertices[vCounter].Log();
				
				if (j < segmentsByDimension) {
					indices[iCounter++] = vCounter;
					indices[iCounter++] = (unsigned short)(vCounter + j + 1);
					indices[iCounter++] = (unsigned short)(vCounter + j + 2);
					if (i > 0) {
						indices[iCounter++] = (unsigned short)(vCounter - 1);
						indices[iCounter++] = (unsigned short)(vCounter + j + 1);
						indices[iCounter++] = (unsigned short)(vCounter);
					}
				}

				vCounter++;
			}
		}
		
		setVertices(vertices, verticesCount);
		setVertexIndices(indices, indicesCount);
	}


public:

	Triangle() {
		init(1, 1);
	}

	Triangle(float size, int segmentsByDimension) {
		init(size, segmentsByDimension);
	}

	Triangle(int segmentsByDimension, Vec3f point1, Vec3f point2, Vec3f point3) {
		init(segmentsByDimension, point1, point2, point3);
	}

};
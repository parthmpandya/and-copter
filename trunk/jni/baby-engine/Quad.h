#pragma once

#include "Group.h"
#include "Triangle.h"

class Quad : public Group {

private:

	void init(float size, int segmentsByDimension) {
		init(segmentsByDimension, 
				Vec3f(-size/2, size/2, 0),
				Vec3f(-size/2, -size/2, 0),
				Vec3f(size/2, -size/2, 0),
				Vec3f(size/2, size/2, 0));
	}

	void init(int segmentsByDimension, Vec3f point1, Vec3f point2, Vec3f point3, Vec3f point4) {
		if (point1 != point2 && point2 != point4 && point1 != point4) {
			add(new Triangle(segmentsByDimension, point1, point2, point4));
		}
		if (point2 != point3 && point3 != point4 && point2 != point4) {
			add(new Triangle(segmentsByDimension, point2, point3, point4));
		}
	}


public:

	Quad() {
		init(1, 1);
	}

	Quad(float size, int segmentsByDimension) {
		init(size, segmentsByDimension);
	}

	Quad(int segmentsByDimension, Vec3f point1, Vec3f point2, Vec3f point3, Vec3f point4) {
		init(segmentsByDimension, point1, point2, point3, point4);
	}

};
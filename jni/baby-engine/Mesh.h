#ifndef MESH_H
#define MESH_H

#include "Vec3f.h"
#include <GLES\gl.h>
#include "RGBA.h"

class Mesh
{

protected:
	Vec3f leftTop;
	Vec3f rightBottom;
	
	Vec3f translation;
	Vec3f rotation;

	int verticesCount;
	Vec3f* vertices;

	int vertexIndicesCount;
	unsigned short * vertexIndices;

	RGBA color;
	int colorsCount;
	RGBA *colorBuffer;

	virtual void calculateBounds();

public:

	Mesh(void) :
		leftTop(0, 0, 0),
		rightBottom(0, 0, 0),
		translation(0, 0, 0),
		rotation(0, 0, 0)		
	{
	}

	virtual ~Mesh(void) {
		if (vertices) {
			delete[] vertices;
		}
		if (colorBuffer) {
			delete[] colorBuffer;
		}
		if (vertexIndices) {
			delete[] vertexIndices;
		}
	}

	void setVertices(Vec3f* vertices, int count) {
		if (this->vertices) {
			delete[] vertices;
		}
		this->vertices = vertices;
		this->verticesCount = count;
		calculateBounds();
	}

	void translate(const Vec3f& translation) {
		this->translation = translation;
	}
	
	void move(const Vec3f& delta) {
		this->translation += delta;
	}
	
	void rotate(const Vec3f& rotation) {
		this->rotation = rotation;
	}

	virtual Vec3f getLeftTop() {
		return leftTop + translation;
	}

	virtual Vec3f getRightBottom() {
		return rightBottom + translation;
	}

	float getWidth() {
		return getRightBottom().x - getLeftTop().x;
	}

	float getHeight() {
		return getLeftTop().y - getRightBottom().y;
	}

	float getDepth() {
		return getRightBottom().z - getLeftTop().z;
	}

	const RGBA getColor() {
		return color;
	}

	virtual void setColor(const RGBA& color) {
		this->color = color;
	}

	void setColorBuffer(RGBA* colorBuffer, int count) {
		if (this->colorBuffer) {
			delete[] colorBuffer;
		}
		this->colorBuffer = colorBuffer;
		this->colorsCount = count;
	}

	void setVertexIndices(unsigned short * vertexIndices, int count) {
		if (this->vertexIndices) {
			delete[] vertexIndices;
		}
		this->vertexIndices = vertexIndices;
		this->vertexIndicesCount = count;
	}

	virtual void draw();

};

#endif

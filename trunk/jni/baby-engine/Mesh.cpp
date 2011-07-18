#include "Mesh.h"

void Mesh::calculateBounds() {
	if (vertices) {
		leftTop = vertices[0];
		rightBottom = vertices[0];
		for (int i = 1; i < verticesCount; i++) {
			vertices[i].UpdateMinMax(leftTop, rightBottom);
		}
	} else {
		leftTop.Set(0, 0, 0);
		rightBottom.Set(0, 0, 0);
	}
}

void Mesh::draw() {
	if (!vertices || !vertexIndices) {
		return;
	}

	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	if (colorBuffer && colorsCount > 0) {
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_FLOAT, 0, colorBuffer);
	} else {
		glColor4f(color.r, color.g, color.b, color.a);
	}
	glPushMatrix();

	glTranslatef(translation.x, translation.y, translation.z);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);

	glDrawElements(GL_TRIANGLES, vertexIndicesCount, GL_UNSIGNED_SHORT, vertexIndices);

	glPopMatrix();
	if (colorBuffer) {
		glDisableClientState(GL_COLOR_ARRAY);
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_CULL_FACE);
}
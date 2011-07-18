#pragma once

#include "Mesh.h"
#include "List.h"

class Group : public Mesh
{
protected:
	List<Mesh*> meshs;

	virtual void calculateBounds() {
		if (meshs.IsEmpty()) {
			leftTop.Set(0, 0, 0);
			rightBottom.Set(0, 0, 0);
		}
		leftTop = meshs.Front()->getLeftTop();
		rightBottom = meshs.Front()->getRightBottom();
		for (Iterator i = meshs; meshs.HasNext(i); meshs.Next(i)) {
			((Vec3f)meshs[i]->getLeftTop()).UpdateMinMax(leftTop, rightBottom);
			((Vec3f)meshs[i]->getRightBottom()).UpdateMinMax(leftTop, rightBottom);
		}
	}

public:

	virtual ~Group(void)
	{
		for (Iterator i = meshs; meshs.HasNext(i); meshs.Next(i)) {
			delete meshs[i];
		}
	}

	void add(Mesh* mesh) {
		meshs.PushBack(mesh);
		calculateBounds();
	}

	void remove(Mesh* mesh) {
		meshs.Remove(mesh);
		calculateBounds();
	}

	virtual void setColor(const RGBA& color) {
		for (Iterator i = meshs; meshs.HasNext(i); meshs.Next(i)) {
			meshs[i]->setColor(color);
		}
	}

	virtual void draw() {
		glPushMatrix();

		glTranslatef(translation.x, translation.y, translation.z);
		glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.z, 0, 0, 1);

		for (Iterator i = meshs; meshs.HasNext(i); meshs.Next(i)) {
			meshs[i]->draw();
		}

		glPopMatrix();
	}
};
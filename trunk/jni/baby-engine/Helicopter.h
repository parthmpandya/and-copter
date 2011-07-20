#pragma once

#include "Quad.h"

class Helicopter : public Group {

private:

	Vec3f velocity;

public:

	Helicopter(float size) :
	  velocity(0,0,0)
	{
		add(new Quad(size, 1));
	}


	void applyGravity(float gravity) {
		velocity += Vec3f(0, gravity, 0);
	}

	void accelerate(float dvy) {
		velocity += Vec3f(0, dvy, 0);
	}

	void move() {
		Group::move(velocity);
	}

	virtual void draw() {		
		Group::draw();
	}
};
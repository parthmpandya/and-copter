#pragma once

#include "Group.h"
#include "Rocks.h"
#include "Helicopter.h"

class Game : public Group {

protected:
	float width;
	float height;

	bool paused;

	float gravity;

	Helicopter* helicopter;
	Rocks* rocks;
public:

	Game(float W, float H);
	virtual ~Game();

	void onScreenSizeChanged(float newW, float newH);
	virtual void draw();

	void moveHelicopter(float dy);
};
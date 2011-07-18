#pragma once

#include "Group.h"

class Game : public Group {

protected:
	float width;
	float height;

public:

	Game(float W, float H);
	virtual ~Game();

	void onScreenSizeChanged(float newW, float newH);
};
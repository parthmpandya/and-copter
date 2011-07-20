#pragma once

#include "Renderer.h"
#include "Game.h"

class AndcopterRenderer : public Renderer {

protected:
	Game* game;

public:

	AndcopterRenderer() :
	  game(0)
	{
		fov_y = 45.0f;
		z_distance = -2;
	}

	virtual ~AndcopterRenderer() {
		if (game) {
			delete game;			
		}
	}

	Game* getGame() {
		return game;
	}

	virtual void onCreate();	
	virtual void onSurfaceChange(int width, int height);
	virtual void onDraw();

};
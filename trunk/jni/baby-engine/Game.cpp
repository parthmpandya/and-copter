#include "Game.h"
#include "Quad.h"

Game::Game(float w, float h) :
	width(w),
	height(h) 
{
	LOGD("new game(w=%f, h=%f)", w, h);
	Mesh *mesh = new Quad();
	add(mesh);
}

Game::~Game() {
}

void Game::onScreenSizeChanged(float newW, float newH) {
	LOGD("game screen size changed (w=%f, h=%f)", newW, newH);
	width = newW;
	height = newH;
}
#include "Game.h"

Game::Game(float w, float h) :
	width(w),
	height(h),
	paused(false),
	gravity(-0.0001f)
{
	LOGD("new game(w=%f, h=%f)", w, h);

	rocks = new Rocks(w, h);
	add(rocks);

	helicopter = new Helicopter(0.15f * height);
	helicopter->translate(Vec3f(-width/2 + helicopter->getWidth()/2 + 0.1f, 0, 0));
	add(helicopter);
}

Game::~Game() {
}

void Game::onScreenSizeChanged(float newW, float newH) {
	LOGD("game screen size changed (w=%f, h=%f)", newW, newH);
	width = newW;
	height = newH;
}

void Game::draw() {
	if (!paused) {
		helicopter->applyGravity(gravity);
		helicopter->move();
		rocks->move();
		if (rocks->has2DCollision(helicopter)) {
			paused = true;
		}
	}
	Group::draw();
}

void Game::moveHelicopter(float dy) {
	helicopter->accelerate(dy);
}
#include "AndcopterRenderer.h"

void AndcopterRenderer::onCreate() {
	glClearColor(0, 0, 0, 0.5f);
	glClearDepthf(1.0f);	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}
	
void AndcopterRenderer::onSurfaceChange(int width, int height) {
	glViewport(0, 0, width, height);		
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = (float) width / height;
	gluPerspective(fov_y, aspect, z_distance, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float gameHeight = (float)(-z_distance * (tan(fov_y * M_PI / 360))) * 2; 
	float gameWidth = gameHeight * aspect;

	if (!game) {
		game = new Game(gameWidth, gameHeight);
	} else {
		game->onScreenSizeChanged(gameWidth, gameHeight);
	}
}

void AndcopterRenderer::onDraw() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	if (game) {
		game->draw();
	}
}
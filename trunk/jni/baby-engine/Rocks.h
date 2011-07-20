#pragma once

#include "Group.h"
#include "Quad.h"

#include "Random.h"

class Rocks : public Group {

private:
	static const float PIECE_HEIGHT_STEP;
	static const float PIECE_MIN_HEIGHT;
	static const float PIECE_MAX_HEIGHT;
	static const float PIECE_WIDTH;
	static const int STEPS_IN_WIDTH; 
	static const float STEP;

	float lastTopHeight;
	float lastBottomHeight;
	
	float pieceMinHeight;
	float pieceMaxHeight;
	float pieceWidth;
	float step;
	
	float width;
	float height;
	int distance;

	Random random;
protected:

	void createNewSurfacePart(bool top);	
	void cleanUpObjects();

public:

	Rocks(float w, float h) :
		lastTopHeight(0),
		lastBottomHeight(0),
		pieceMinHeight(h/2 * PIECE_MIN_HEIGHT),
		pieceMaxHeight(h/2 * PIECE_MAX_HEIGHT),
		pieceWidth(w/2 * PIECE_WIDTH),
		step(w/2 * STEP),
		width(w),
		height(h),
		distance(0),
		random()
	{
		createNewSurfacePart(true);
		createNewSurfacePart(false);
	}

	void move();
	virtual void draw();
	virtual bool has2DCollision(Mesh* mesh);
};
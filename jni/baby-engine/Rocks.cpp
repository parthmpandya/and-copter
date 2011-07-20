#include "Rocks.h"

const float Rocks::PIECE_HEIGHT_STEP = 0.05f;
const float Rocks::PIECE_MIN_HEIGHT = PIECE_HEIGHT_STEP;
const float Rocks::PIECE_MAX_HEIGHT = PIECE_HEIGHT_STEP * 8;
const float Rocks::PIECE_WIDTH = 0.07f;
const int Rocks::STEPS_IN_WIDTH = 5; 
const float Rocks::STEP = PIECE_WIDTH / STEPS_IN_WIDTH;

void Rocks::createNewSurfacePart(bool top) {
	float lastHeight = top ? lastTopHeight : lastBottomHeight;
	float height = lastHeight + ((random.next(3) - 1) * PIECE_HEIGHT_STEP) * this->height/2;
	if (height < pieceMinHeight) {
		height = pieceMinHeight;
	} else if (height > pieceMaxHeight) {
		height = pieceMaxHeight;
	}
	Mesh *result = 0;        
	if (height > lastHeight) {
		result = new Quad(1, 
				Vec3f(-pieceWidth/2, top ? (height/2) : (lastHeight - height/2), 0),
				Vec3f(-pieceWidth/2, top ? (height/2 - lastHeight) : (-height/2) , 0),
				Vec3f(pieceWidth/2, -height/2, 0),
				Vec3f(pieceWidth/2, height/2, 0));
		result->translate(Vec3f(
			width / 2 + pieceWidth, 
			(top ? 1 : -1) * ((this->height / 2) - (height / 2)), 
			0));
	} else {
		result = new Quad(1, 
				Vec3f(-pieceWidth/2, lastHeight/2, 0),
				Vec3f(-pieceWidth/2, -lastHeight/2, 0),
				Vec3f(pieceWidth/2, top ? (lastHeight/2 - height) : (-lastHeight/2), 0),
				Vec3f(pieceWidth/2, top ? (lastHeight/2) : (height - lastHeight/2), 0));
		result->translate(Vec3f(
			width / 2 + pieceWidth, 
			(top ? 1 : -1) * ((this->height / 2) - (lastHeight / 2)), 
			0));
	}
		
	if (top) {
		lastTopHeight = height;
	} else {
		lastBottomHeight = height;
	}

	add(result);
}

void Rocks::move() {
	for (Iterator i = meshs; meshs.HasNext(i); meshs.Next(i)) {
		meshs[i]->move(Vec3f(-step, 0, 0));
	}
	distance++;
}

void Rocks::cleanUpObjects() {
	for (MutableIterator i = meshs; meshs.HasNext(i); meshs.Next(i)) {
		Mesh* mesh = meshs[i];
		if (mesh->getRightBottom().x < -(width / 2)) {
			meshs.Erase(i);
			delete mesh;
		}
	}
}

void Rocks::draw() {
	if (distance % STEPS_IN_WIDTH == 0) {
		createNewSurfacePart(true);
		createNewSurfacePart(false);
		cleanUpObjects();        
	}
	Group::draw();
}

bool Rocks::has2DCollision(Mesh* mesh) {
	for (Iterator i = meshs; meshs.HasNext(i); meshs.Next(i)) {
		if (meshs[i]->has2DCollision(mesh)) {
			return true;
		}
	}
	return false;
}
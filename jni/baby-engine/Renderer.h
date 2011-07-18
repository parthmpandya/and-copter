#pragma once

#include <GLES\gl.h>
#include <math.h>

class Renderer {

protected:
	int width;
	int height;

	float fov_y;
	float z_distance;

	void gluPerspective(GLfloat fovy, GLfloat aspect,
						   GLfloat zNear, GLfloat zFar)
	{
		GLfloat xmin, xmax, ymin, ymax;

		ymax = zNear * (GLfloat)tan(fovy * M_PI / 360);
		ymin = -ymax;
		xmin = ymin * aspect;
		xmax = ymax * aspect;

		glFrustumx((GLfixed)(xmin * 65536), (GLfixed)(xmax * 65536),
				   (GLfixed)(ymin * 65536), (GLfixed)(ymax * 65536),
				   (GLfixed)(zNear * 65536), (GLfixed)(zFar * 65536));
	}
	
public:

	virtual void onCreate() = 0;
	virtual void onSurfaceChange(int width, int height) = 0;
	virtual void onDraw() = 0;

};
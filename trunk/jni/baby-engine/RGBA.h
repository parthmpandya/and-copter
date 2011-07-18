#pragma once
class RGBA
{
public:

	float r, g, b, a;

	RGBA(void) :
		r(0),
		g(0),
		b(0),
		a(0)
	{
	}

	RGBA(float R, float G, float B, float A)  :
		r(R),
		g(G),
		b(B),
		a(A)
	{
	}

	operator float*() { 
		return (float *)&r; 
	}

	operator const float*() const { 
		return &r; 
	}

	~RGBA(void)
	{
	}
};


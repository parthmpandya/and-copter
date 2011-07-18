#pragma once
class RGBA
{
public:

	float r, g, b, a;

	RGBA(void)
	{
	}

	RGBA(float R, float G, float B, float A) {
		a = A;
		g = G;
		b = B;
		a = A;
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


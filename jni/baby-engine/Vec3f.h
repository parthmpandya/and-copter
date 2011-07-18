#ifndef VEC3F_H
#define VEC3F_H

#include "Log.h"
#include <math.h>

class Vec3f
{
  public:
	float x, y, z;

	Vec3f(void) {
	};

	Vec3f(const float X, const float Y, const float Z) {
		x=X; 
		y=Y; 
		z=Z; 
	};

	Vec3f(const Vec3f& v) { 
		x=v.x; 
		y=v.y; 
		z=v.z; 
	};

	Vec3f(float v[3]) {
		x=v[0]; 
		y=v[1]; 
		z=v[2]; 
	};

	void Set(const float X, const float Y, const float Z) { 
		x=X; 
		y=Y; 
		z=Z; 
	}

	void Set (float v[3]) { 
		x=v[0]; 
		y=v[1]; 
		z=v[2]; 
	};

	// FLOAT * CONVERSION
	operator float*() { 
		return (float *)&x; 
	}

	// CONST FLOAT * CONVERSION
	operator const float*() const { 
		return &x; 
	}

	// COMPARISON (==)
	int operator == (const Vec3f& A) { 
		return (x==A.x && y==A.y && z==A.z); 
	}

	// ASSIGNMENT (=)
	Vec3f& operator = (const Vec3f& A) { 
		x=A.x; 
		y=A.y; 
		z=A.z; 
		return(*this);
	};

	// ADDITION (+)
	Vec3f operator + (const Vec3f& A) const { 
		Vec3f Sum(x+A.x, y+A.y, z+A.z); 
		return(Sum); 
	};

	// SUBTRACTION (-)
	Vec3f operator - (const Vec3f& A) const       
	  { Vec3f Diff(x-A.x, y-A.y, z-A.z);
		return(Diff); };

	// DOT-PRODUCT (*)
	float operator * (const Vec3f& A) const       
	  { float DotProd = x*A.x+y*A.y+z*A.z; 
		return(DotProd); };

	// CROSS-PRODUCT (/)
	Vec3f operator / (const Vec3f& A) const       
	  { Vec3f CrossProd(y*A.z-z*A.y, z*A.x-x*A.z, x*A.y-y*A.x);
		return(CrossProd); };

	// MULTIPLY BY SCALAR V*s (*)
	Vec3f operator * (const float s) const        
	  { Vec3f Scaled(x*s, y*s, z*s); 
		return(Scaled); };

	// DIVIDE BY SCALAR (/)
	Vec3f operator / (const float s) const        
	  { Vec3f Scaled(x/s, y/s, z/s);
		return(Scaled); };

	// SCALAR MULT s*V
	friend inline Vec3f operator *(float s, const Vec3f& v)  
	  { return Vec3f(v.x*s, v.y*s, v.z*s); }

	// ACCUMULATED VECTOR ADDITION (+=)
	void operator += (const Vec3f A)              
	  { x+=A.x; y+=A.y; z+=A.z; };

	// ACCUMULATED VECTOR SUBTRACTION (+=)
	void operator -= (const Vec3f A)              
	  { x-=A.x; y-=A.y; z-=A.z; };

	// ACCUMULATED SCALAR MULT (*=)
	void operator *= (const float s)              
	  { x*=s; y*=s; z*=s; };

	// ACCUMULATED SCALAR DIV (/=)
	void operator /= (const float s)              
	  { x/=s; y/=s; z/=s; };

	// NEGATION (-)
	Vec3f operator - (void) const                 
	  { Vec3f Negated(-x, -y, -z);
		return(Negated); };

	// LENGTH OF VECTOR
	float Length (void) const                     
	  { return ((float)sqrt(x*x+y*y+z*z)); };

	// LENGTH OF VECTOR (SQUARED)
	float LengthSqr (void) const                  
	  { return (x*x+y*y+z*z); };

	// NORMALIZE VECTOR
	void Normalize (void)                         
	  { float L = Length();                       
		if (L>0) { x/=L; y/=L; z/=L; } };         

	void UpdateMinMax(Vec3f &Min, Vec3f &Max)
	{
	  if (x<Min.x) Min.x=x; else if (x>Max.x) Max.x=x;
	  if (y<Min.y) Min.y=y; else if (y>Max.y) Max.y=y;
	  if (z<Min.z) Min.z=z; else if (z>Max.z) Max.z=z;
	}

	void Log() { 
		LOGD("(%.3f, %.3f, %.3f)", x, y, z); 
	}
};

#endif
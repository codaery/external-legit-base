#pragma once
#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)
#define FastSqrt(x)			(*sqrtf)(x)
#define M_PI		3.14159265358979323846

struct vector {
	float x, y, z;
};

typedef struct {
	float matrix[3][4];
}matrix;

typedef struct {
	float flMatrix[4][4];
}world_to_screen_matrix;

class vector3
{
public:
	float x, y, z;
	vector3(void);
	vector3(float X, float Y, float Z);
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	bool IsValid() const;
	float operator[](int i) const;
	float& operator[](int i);
	inline void Zero();
	bool operator==(const vector3& v) const;
	bool operator!=(const vector3& v) const;
	__forceinline vector3& operator+=(const vector3& v);
	__forceinline vector3& operator-=(const vector3& v);
	__forceinline vector3& operator*=(const vector3& v);
	__forceinline vector3& operator*=(float s);
	__forceinline vector3& operator/=(const vector3& v);
	__forceinline vector3& operator/=(float s);
	__forceinline vector3& operator+=(float fl);
	__forceinline vector3& operator-=(float fl);
	inline float	Length() const;
	__forceinline float LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (x * x + y * y + z * z);
	}
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance&&
			y > -tolerance && y < tolerance&&
			z > -tolerance && z < tolerance);
	}
	float	NormalizeInPlace();
	inline vector3 Normalizevector3();
	__forceinline float	DistToSqr(const vector3& vOther) const;
	float	Dot(const vector3& vOther) const;
	float	Length2D(void) const;
	float	Length2DSqr(void) const;
	vector3& operator=(const vector3& vOther);
	vector3	operator-(void) const;
	vector3	operator+(const vector3& v) const;
	vector3	operator-(const vector3& v) const;
	vector3	operator*(const vector3& v) const;
	vector3	operator/(const vector3& v) const;
	vector3	operator*(float fl) const;
	vector3	operator/(float fl) const;
	// Base address...
	float* Base();
	float const* Base() const;
};

//===============================================
inline void vector3::Init(float ix, float iy, float iz)
{
	x = ix; y = iy; z = iz;
	CHECK_VALID(*this);
}
//===============================================
inline vector3::vector3(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
	CHECK_VALID(*this);
}
//===============================================
inline vector3::vector3(void) { x = y = z = 0; }
//===============================================
inline void vector3::Zero()
{
	x = y = z = 0.0f;
}
//===============================================
inline void vector3Clear(vector3& a)
{
	a.x = a.y = a.z = 0.0f;
}
//===============================================
inline vector3& vector3::operator=(const vector3& vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}
//===============================================
inline float& vector3::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline float vector3::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline bool vector3::operator==(const vector3& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y) && (src.z == z);
}
//===============================================
inline bool vector3::operator!=(const vector3& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y) || (src.z != z);
}
//===============================================
__forceinline void vector3Copy(const vector3& src, vector3& dst)
{
	CHECK_VALID(src);
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}
//===============================================
__forceinline  vector3& vector3::operator+=(const vector3& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y; z += v.z;
	return *this;
}
//===============================================
__forceinline  vector3& vector3::operator-=(const vector3& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}
//===============================================
__forceinline  vector3& vector3::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline  vector3& vector3::operator*=(const vector3& v)
{
	CHECK_VALID(v);
	x *= v.x;
	y *= v.y;
	z *= v.z;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline vector3& vector3::operator+=(float fl)
{
	x += fl;
	y += fl;
	z += fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline vector3& vector3::operator-=(float fl)
{
	x -= fl;
	y -= fl;
	z -= fl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline  vector3& vector3::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
__forceinline  vector3& vector3::operator/=(const vector3& v)
{
	CHECK_VALID(v);
	Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
	x /= v.x;
	y /= v.y;
	z /= v.z;
	CHECK_VALID(*this);
	return *this;
}
//===============================================
inline float vector3::Length(void) const
{
	CHECK_VALID(*this);

	float root = 0.0f;

	float sqsr = x * x + y * y + z * z;

	__asm
	{
		sqrtss xmm0, sqsr
		movss root, xmm0
	}

	return root;
}
//===============================================
inline float vector3::Length2D(void) const
{
	CHECK_VALID(*this);

	float root = 0.0f;

	float sqst = x * x + y * y;

	__asm
	{
		sqrtss xmm0, sqst
		movss root, xmm0
	}

	return root;
}
//===============================================
inline float vector3::Length2DSqr(void) const
{
	return (x * x + y * y);
}
//===============================================
inline vector3 CrossProduct(const vector3& a, const vector3& b)
{
	return vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
//===============================================
float vector3::DistToSqr(const vector3& vOther) const
{
	vector3 delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.LengthSqr();
}
//===============================================
inline float vector3::NormalizeInPlace()
{
	vector3& v = *this;

	float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

	v.x *= iradius;
	v.y *= iradius;
	v.z *= iradius;

	return iradius;
}

vector3 vector3::Normalizevector3()
{
	vector3 v;
	float length = this->Length();

	if (length != 0)
	{
		v.x = x / length;
		v.y = y / length;
		v.z = z / length;
	}
	else
	{
		v.x = v.y = 0.0f; v.z = 1.0f;
	}

	return v;
}

//===============================================
inline float vector3Normalize(vector3& v)
{
	Assert(v.IsValid());
	float l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		// FIXME: 
		// Just copying the existing implemenation; shouldn't res.z == 0?
		v.x = v.y = 0.0f; v.z = 1.0f;
	}
	return l;
}
//===============================================
__forceinline float vector3Normalize(float* v)
{
	return vector3Normalize(*(reinterpret_cast<vector3*>(v)));
}
//===============================================
inline vector3 vector3::operator+(const vector3& v) const
{
	vector3 res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

//===============================================
inline vector3 vector3::operator-(const vector3& v) const
{
	vector3 res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}
//===============================================
inline vector3 vector3::operator*(float fl) const
{
	vector3 res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}
//===============================================
inline vector3 vector3::operator*(const vector3& v) const
{
	vector3 res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}
//===============================================
inline vector3 vector3::operator/(float fl) const
{
	vector3 res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}
//===============================================
inline vector3 vector3::operator/(const vector3& v) const
{
	vector3 res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}
inline float vector3::Dot(const vector3& vOther) const
{
	const vector3& a = *this;

	return(a.x * vOther.x + a.y * vOther.y + a.z * vOther.z);
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------

inline float vector3Length(const vector3& v)
{
	CHECK_VALID(v);
	return (float)FastSqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

//vector3 SUBTRAC
inline void vector3Subtract(const vector3& a, const vector3& b, vector3& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

//vector3ADD
inline void vector3Add(const vector3& a, const vector3& b, vector3& c)
{
	CHECK_VALID(a);
	CHECK_VALID(b);
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* vector3::Base()
{
	return (float*)this;
}

inline float const* vector3::Base() const
{
	return (float const*)this;
}

FORCEINLINE void vector3MAInline(const float* start, float scale, const float* direction, float* dest)
{
	dest[0] = start[0] + direction[0] * scale;
	dest[1] = start[1] + direction[1] * scale;
	dest[2] = start[2] + direction[2] * scale;
}

FORCEINLINE void vector3MAInline(const vector3& start, float scale, const vector3& direction, vector3& dest)
{
	dest.x = start.x + direction.x * scale;
	dest.y = start.y + direction.y * scale;
	dest.z = start.z + direction.z * scale;
}

FORCEINLINE void vector3MA(const vector3& start, float scale, const vector3& direction, vector3& dest)
{
	vector3MAInline(start, scale, direction, dest);
}

FORCEINLINE void vector3MA(const float* start, float scale, const float* direction, float* dest)
{
	vector3MAInline(start, scale, direction, dest);
}
FORCEINLINE float DotProduct(const vector3& a, const vector3& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

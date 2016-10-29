// cyCodeBase by Cem Yuksel
// [www.cemyuksel.com]
//-------------------------------------------------------------------------------
///
/// \file		cyPoint.h 
/// \author		Cem Yuksel
/// \version	1.4
/// \date		September 3, 2012
///
/// \brief 2D, 3D and 4D point classes.
///
///
/// @copydoc cyPoint3
///
/// cyPoint3 is 3D point class
///
/// You can use point classes with OpenGL as
///
/// glVertex3f( myvector.x, myvector.y, myvector.z );
///
/// or
///
/// glVertex3fv( &myvector.x );
///
//-------------------------------------------------------------------------------

#ifndef _CY_POINT_H_INCLUDED_
#define _CY_POINT_H_INCLUDED_

//-------------------------------------------------------------------------------

#include <math.h>

//-------------------------------------------------------------------------------

/// 2D point class

template <class T>
class cyPoint2
{
	friend cyPoint2 operator+( const T v, const cyPoint2 &pt ) { return pt+v; }		///< Addition with a constant
	friend cyPoint2 operator-( const T v, const cyPoint2 &pt ) { return -(pt-v); }	///< Subtraction from a constant
	friend cyPoint2 operator*( const T v, const cyPoint2 &pt ) { return pt*v; }		///< Multiplication with a constant

public:
	typedef T Scalar;

	T x, y;

	///@name Constructors
	cyPoint2() {}
	cyPoint2( T _x, T _y ) { x=_x; y=_y; }
	cyPoint2( const T *pt ) { x=pt[0]; y=pt[1]; }
	cyPoint2( const cyPoint2 &pt ) { x=pt.x; y=pt.y; }

	///@name Set & Get value functions
	cyPoint2& Zero() { x=0; y=0; return *this; }						///< Sets x and y coordinates as zero
	cyPoint2& Set( T _x, T _y ) { x=_x; y=_y; return *this; }	///< Sets x and y coordinates as given
	cyPoint2& Set( const T *v ) { x=v[0]; y=v[1]; return *this; }	///< Sets x and y coordinates using the values in the given array
	void GetValue( T *v ) const { v[0]=x; v[1]=y; }					///< Puts x and y values into the array

	///@name Length and Normalize functions
	void		Normalize()		{ T s = (1.0f)/Length(); *this *= s; }
	cyPoint2	GetNormalized() const { T s = (1.0f)/Length(); return *this * s; }
	T		LengthSquared()	const { return x*x + y*y; }
	T		Length()		const { return (T) sqrt(LengthSquared()); }

	///@name Limit functions
	void ClampMinMax( T minValue, T maxValue ) { ClampMin(minValue); ClampMax(maxValue); }
	void ClampMin( T n ) { if(x<n)x=n; if(y<n)y=n; }
	void ClampMax( T n ) { if(x>n)x=n; if(y>n)y=n; }

	///@name Unary operators
	cyPoint2 operator-() const { return cyPoint2(-x,-y); } 
	cyPoint2 operator+() const { return *this; }

	///@name Binary operators
	cyPoint2 operator+( const cyPoint2 &pt ) const { return cyPoint2(x+pt.x, y+pt.y); }
	cyPoint2 operator-( const cyPoint2 &pt ) const { return cyPoint2(x-pt.x, y-pt.y); }
	cyPoint2 operator*( const cyPoint2 &pt ) const { return cyPoint2(x*pt.x, y*pt.y); }
	cyPoint2 operator/( const cyPoint2 &pt ) const { return cyPoint2(x/pt.x, y/pt.y); }
	cyPoint2 operator+(T n) const { return cyPoint2(x+n, y+n); }
	cyPoint2 operator-(T n) const { return cyPoint2(x-n, y-n); }
	cyPoint2 operator*(T n) const { return cyPoint2(x*n, y*n); }
	cyPoint2 operator/(T n) const { return cyPoint2(x/n, y/n); }

	///@name Assignment operators
	cyPoint2& operator+=( const cyPoint2 &pt ) { x+=pt.x; y+=pt.y; return *this; }
	cyPoint2& operator-=( const cyPoint2 &pt ) { x-=pt.x; y-=pt.y; return *this; }
	cyPoint2& operator*=( const cyPoint2 &pt ) { x*=pt.x; y*=pt.y; return *this; }
	cyPoint2& operator/=( const cyPoint2 &pt ) { x/=pt.x; y/=pt.y; return *this; }
	cyPoint2& operator+=(T n) { x+=n; y+=n; return *this; }
	cyPoint2& operator-=(T n) { x-=n; y-=n; return *this; }
	cyPoint2& operator*=(T n) { x*=n; y*=n; return *this; }
	cyPoint2& operator/=(T n) { x/=n; y/=n; return *this; }

	///@name Test operators
	int operator==( const cyPoint2& pt ) const { return ( (pt.x==x) && (pt.y==y) ); }
	int operator!=( const cyPoint2& pt ) const { return ( (pt.x!=x) || (pt.y!=y) ); }

	///@name Access operators
	T& operator[]( int i ) { return (&x)[i]; }
	T  operator[]( int i ) const { return (&x)[i]; }

	///@name Cross product and dot product
	T Cross	   ( const cyPoint2 &pt ) const { return x*pt.y-y*pt.x; }		///< Cross product
	T operator^( const cyPoint2 &pt ) const { return Cross(pt); }			///< Cross product operator
	T Dot	   ( const cyPoint2 &pt ) const { return x*pt.x + y*pt.y; }	///< Dot product
	T operator%( const cyPoint2 &pt ) const { return Dot(pt); }			///< Dot product operator

};




//-------------------------------------------------------------------------------


/// 3D point class

template <class T>
class cyPoint3
{
	friend cyPoint3 operator+( const T v, const cyPoint3 &pt ) { return pt+v; }		///< Addition with a constant
	friend cyPoint3 operator-( const T v, const cyPoint3 &pt ) { return -(pt-v); }	///< Subtraction from a constant
	friend cyPoint3 operator*( const T v, const cyPoint3 &pt ) { return pt*v; }		///< Multiplication with a constant

public:
	typedef T Scalar;

	T x, y, z;

	///@name Constructors
	cyPoint3() { }
	cyPoint3( T _x, T _y, T _z ) { x=_x; y=_y; z=_z; }
	cyPoint3( const T *pt ) { x=pt[0]; y=pt[1]; z=pt[2]; }
	cyPoint3( const cyPoint3 &pt ) { x=pt.x; y=pt.y; z=pt.z; }
	cyPoint3( const cyPoint2<T> &pt ) { x=pt.x; y=pt.y; z=0.0f; }
	cyPoint3( const cyPoint2<T> &pt, T _z ) { x=pt.x; y=pt.y; z=_z; }

	///@name Set & Get value functions
	cyPoint3& Zero() { x=0; y=0; z=0; return *this; }									///< Sets x, y and z coordinates as zero
	cyPoint3& Set( T _x, T _y, T _z ) { x=_x; y=_y; z=_z; return *this; }	///< Sets x, y and z coordinates as given
	cyPoint3& Set( const T *v ) { x=v[0]; y=v[1]; z=v[2]; return *this; }			///< Sets x, y and z coordinates using the values in the given array
	void GetValue( T *v ) const { v[0]=x; v[1]=y; v[2]=z; }							///< Puts x, y and z values into the array

	///@name Length and Normalize functions
	void		Normalize()		{ T s = (1.0f)/Length(); *this *= s; }
	cyPoint3	GetNormalized()	const { T s = (1.0f)/Length(); return *this * s; }
	T		LengthSquared()	const { return x*x + y*y + z*z; }
	T		Length()		const { return (T) sqrt(LengthSquared()); }

	///@name Limit functions
	void ClampMinMax( T min, T max ) { ClampMin(min); ClampMax(max); }
	void ClampMin( T n ) { if(x<n)x=n; if(y<n)y=n; if(z<n)z=n; }
	void ClampMax( T n ) { if(x>n)x=n; if(y>n)y=n; if(z>n)z=n; }

	///@name Unary operators
	cyPoint3 operator-() const { return cyPoint3(-x,-y,-z); } 
	cyPoint3 operator+() const { return *this; }

	///@name Binary operators
	cyPoint3 operator+( const cyPoint3 &pt ) const { return cyPoint3(x+pt.x, y+pt.y, z+pt.z); }
	cyPoint3 operator-( const cyPoint3 &pt ) const { return cyPoint3(x-pt.x, y-pt.y, z-pt.z); }
	cyPoint3 operator*( const cyPoint3 &pt ) const { return cyPoint3(x*pt.x, y*pt.y, z*pt.z); }
	cyPoint3 operator/( const cyPoint3 &pt ) const { return cyPoint3(x/pt.x, y/pt.y, z/pt.z); }
	cyPoint3 operator+(T n) const { return cyPoint3(x+n, y+n, z+n); }
	cyPoint3 operator-(T n) const { return cyPoint3(x-n, y-n, z-n); }
	cyPoint3 operator*(T n) const { return cyPoint3(x*n, y*n, z*n); }
	cyPoint3 operator/(T n) const { return cyPoint3(x/n, y/n, z/n); }

	///@name Assignment operators
	cyPoint3& operator+=( const cyPoint3 &pt ) { x+=pt.x; y+=pt.y; z+=pt.z; return *this; }
	cyPoint3& operator-=( const cyPoint3 &pt ) { x-=pt.x; y-=pt.y; z-=pt.z; return *this; }
	cyPoint3& operator*=( const cyPoint3 &pt ) { x*=pt.x; y*=pt.y; z*=pt.z; return *this; }
	cyPoint3& operator/=( const cyPoint3 &pt ) { x/=pt.x; y/=pt.y; z/=pt.z; return *this; }
	cyPoint3& operator+=(T n) { x+=n; y+=n; z+=n; return *this; }
	cyPoint3& operator-=(T n) { x-=n; y-=n; z-=n; return *this; }
	cyPoint3& operator*=(T n) { x*=n; y*=n; z*=n; return *this; }
	cyPoint3& operator/=(T n) { x/=n; y/=n; z/=n; return *this; }

	///@name Test operators
	int operator==( const cyPoint3& pt ) const { return ( (pt.x==x) && (pt.y==y) && (pt.z==z) ); }
	int operator!=( const cyPoint3& pt ) const { return ( (pt.x!=x) || (pt.y!=y) || (pt.z!=z) ); }

	///@name Access operators
	T& operator[]( int i ) { return (&x)[i]; }
	T  operator[]( int i ) const { return (&x)[i]; }

	///@name Cross product and dot product
	cyPoint3	Cross	 ( const cyPoint3 pt ) const { return cyPoint3(y*pt.z-z*pt.y, z*pt.x-x*pt.z, x*pt.y-y*pt.x); }	///< Cross product
	cyPoint3	operator^( const cyPoint3 pt ) const { return Cross(pt); }					///< Cross product
	T		Dot		 ( const cyPoint3 pt ) const { return x*pt.x + y*pt.y + z*pt.z; }	///< Dot product
	T		operator%( const cyPoint3 pt ) const { return Dot(pt); }					///< Dot product

	///@name Conversion Methods
	cyPoint2<T>	XY() const { return cyPoint2<T>(x,y); }
};

//-------------------------------------------------------------------------------


/// 4D point class
template <class T>
class cyPoint4
{
	friend cyPoint4 operator+( const T v, const cyPoint4 &pt ) { return pt+v; }		///< Addition with a constant
	friend cyPoint4 operator-( const T v, const cyPoint4 &pt ) { return -(pt-v); }	///< Subtraction from a constant
	friend cyPoint4 operator*( const T v, const cyPoint4 &pt ) { return pt*v; }		///< Multiplication with a constant

public:
	typedef T Scalar;

	T x, y, z, w;

	///@name Constructors
	cyPoint4() { }
	cyPoint4( T _x, T _y, T _z, T _w ) { x=_x; y=_y; z=_z; w=_w; }
	cyPoint4( const T *pt ) { x=pt[0]; y=pt[1]; z=pt[2]; w=pt[3]; }
	cyPoint4( const cyPoint4 &pt ) { x=pt.x; y=pt.y; z=pt.z; w=pt.w; }
	cyPoint4( const cyPoint3<T> &pt ) { x=pt.x; y=pt.y; z=pt.z; w=1.0f; }
	cyPoint4( const cyPoint3<T> &pt, T _w ) { x=pt.x; y=pt.y; z=pt.z; w=_w; }

	///@name Set & Get value functions
	cyPoint4& Zero() { x=0; y=0; z=0; w=0; return *this; }												///< Sets x, y, z and w coordinates as zero
	cyPoint4& Set( T _x, T _y, T _z, T _w ) { x=_x; y=_y; z=_z; w=_w; return *this; }	///< Sets x, y, z and w coordinates as given
	cyPoint4& Set( const T *v ) { x=v[0]; y=v[1]; z=v[2]; w=v[3]; return *this; }					///< Sets x, y, z and w coordinates using the values in the given array
	void GetValue( T *v ) const { v[0]=x; v[1]=y; v[2]=z; v[3]=w; }									///< Puts x, y, z and w values into the array

	///@name Length and Normalize functions
	void		Normalize()		{ T s = (1.0f)/Length(); *this *= s; }
	cyPoint4	GetNormalized() const { T s = (1.0f)/Length(); return *this * s; }
	T		LengthSquared()	const { return x*x + y*y + z*z + w*w; }
	T		Length()		const { return (T) sqrt(LengthSquared()); }

	///@name Limit functions
	void ClampMinMax( T min, T max ) { ClampMin(min); ClampMax(max); }
	void ClampMin( T n ) { if(x<n)x=n; if(y<n)y=n; if(z<n)z=n; if(w<n)w=n; }
	void ClampMax( T n ) { if(x>n)x=n; if(y>n)y=n; if(z>n)z=n; if(w>n)w=n; }

	///@name Unary operators
	cyPoint4 operator-() const { return cyPoint4(-x,-y,-z,-w); } 
	cyPoint4 operator+() const { return *this; }

	///@name Binary operators
	cyPoint4 operator+( const cyPoint4 &pt ) const { return cyPoint4(x+pt.x, y+pt.y, z+pt.z, w+pt.w); }
	cyPoint4 operator-( const cyPoint4 &pt ) const { return cyPoint4(x-pt.x, y-pt.y, z-pt.z, w-pt.w); }
	cyPoint4 operator*( const cyPoint4 &pt ) const { return cyPoint4(x*pt.x, y*pt.y, z*pt.z, w*pt.w); }
	cyPoint4 operator/( const cyPoint4 &pt ) const { return cyPoint4(x/pt.x, y/pt.y, z/pt.z, w/pt.w); }
	cyPoint4 operator+(T n) const { return cyPoint4(x+n, y+n, z+n, w+n); }
	cyPoint4 operator-(T n) const { return cyPoint4(x-n, y-n, z-n, w-n); }
	cyPoint4 operator*(T n) const { return cyPoint4(x*n, y*n, z*n, w*n); }
	cyPoint4 operator/(T n) const { return cyPoint4(x/n, y/n, z/n, w/n); }

	///@name Assignment operators
	cyPoint4& operator+=( const cyPoint4 &pt ) { x+=pt.x; y+=pt.y; z+=pt.z; w+=pt.w; return *this; }
	cyPoint4& operator-=( const cyPoint4 &pt ) { x-=pt.x; y-=pt.y; z-=pt.z; w-=pt.w; return *this; }
	cyPoint4& operator*=( const cyPoint4 &pt ) { x*=pt.x; y*=pt.y; z*=pt.z; w*=pt.w; return *this; }
	cyPoint4& operator/=( const cyPoint4 &pt ) { x/=pt.x; y/=pt.y; z/=pt.z; w/=pt.w; return *this; }
	cyPoint4& operator+=(T n) { x+=n; y+=n; z+=n; w+=n; return *this; }
	cyPoint4& operator-=(T n) { x-=n; y-=n; z-=n; w-=n; return *this; }
	cyPoint4& operator*=(T n) { x*=n; y*=n; z*=n; w*=n; return *this; }
	cyPoint4& operator/=(T n) { x/=n; y/=n; z/=n; w/=n; return *this; }

	///@name Test operators
	int operator==( const cyPoint4& pt ) const { return ( (pt.x==x) && (pt.y==y) && (pt.z==z) && (pt.w==w) ); }
	int operator!=( const cyPoint4& pt ) const { return ( (pt.x!=x) || (pt.y!=y) || (pt.z!=z) || (pt.w!=w) ); }

	///@name Access operators
	T& operator[]( int i ) { return (&x)[i]; }
	T  operator[]( int i ) const { return (&x)[i]; }

	///@ Dot product
	T		Dot		 ( const cyPoint4 pt ) const { return x*pt.x + y*pt.y + z*pt.z + w*pt.w; }	///< Dot product
	T		operator%( const cyPoint4 pt ) const { return Dot(pt); }							///< Dot product

	///@name Conversion Methods
	cyPoint2<T>	XY() const { return cyPoint2<T>(x,y); }
	cyPoint3<T>	XYZ() const { return cyPoint3<T>(x,y,z); }
};

//-------------------------------------------------------------------------------


namespace cy {
	typedef cyPoint2<float> Point2f;
	typedef cyPoint3<float> Point3f;
	typedef cyPoint4<float> Point4f;

	typedef cyPoint2<double> Point2d;
	typedef cyPoint3<double> Point3d;
	typedef cyPoint4<double> Point4d;
}

//-------------------------------------------------------------------------------

#endif


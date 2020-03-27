#pragma once
#include "Vector.h"

class RecF
{
public:
	RecF() = default;
	RecF( float left_in,float right_in,float top_in,float bottem_in );
	RecF( const Vec2f& topleft,const Vec2f& bottemright );
	RecF( const Vec2f& topleft,float width,float height );
	bool isOverlappingWith( const RecF& other ) const;
	bool isOverlappingWith( const Vec2f& other ) const;
	static RecF fromCenter( const Vec2f & center,float width,float height );
public:
	float left;
	float right;
	float top;
	float bottem;
};

//---------------------------------------------------------------------------//

class RecI
{
public:
	RecI() = default;
	RecI( int left_in,int right_in,int top_in,int bottem_in );
	RecI( const Vec2i& topleft,const Vec2i& bottemright );
	RecI( const Vec2i& topleft,int width,int height );
	bool isOverlappingWith( const RecI& other ) const;
	bool isOverlappingWith( const Vec2i& other ) const;
	static RecI fromCenter( const Vec2i& center,int width,int height );
public:
	int left;
	int right;
	int top;
	int bottem;
};

#pragma once

class Vec2f
{
public:
	Vec2f() = default;
	Vec2f( float x_in , float y_in );
	Vec2f operator+( const Vec2f& rhs ) const;
	Vec2f& operator+=( const Vec2f& rhs );
	Vec2f operator-( const Vec2f& rhs ) const;
	Vec2f& operator-=( const Vec2f& rhs );
	Vec2f operator*( float rhs ) const;
	Vec2f& operator*=( float rhs );
	Vec2f operator/( float rhs ) const;
	Vec2f& operator/=( float rhs );
	bool operator==( const Vec2f& rhs ) const;
	float getLength() const;
	float getLengthSq() const;
	Vec2f& Nomalize();
	Vec2f getNomalize() const;
public:
	float x;
	float y;
};

//------------------------------------------------//

class Vec2i
{
public:
	Vec2i() = default;
	Vec2i( int x_in,int y_in );
	Vec2i operator+( const Vec2i& rhs ) const;
	Vec2i& operator+=( const Vec2i& rhs );
	Vec2i operator-( const Vec2i& rhs ) const;
	Vec2i& operator-=( const Vec2i& rhs );
	Vec2i operator*( int rhs ) const;
	Vec2i& operator*=( int rhs );
	Vec2i operator/( int rhs ) const;
	Vec2i& operator/=( int rhs );
	bool operator==( const Vec2i& rhs ) const;
	float getLength() const;
	float getLengthSq() const;
	Vec2i& Nomalize();
	Vec2i getNomalize() const;
public:
	int x;
	int y;
};

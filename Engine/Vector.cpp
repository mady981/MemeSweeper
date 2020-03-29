#include "Vector.h"
#include <cmath>

Vec2f::Vec2f(float x_in, float y_in)
	:
	x( x_in ),
	y( y_in )
{
}

Vec2f Vec2f::operator+(const Vec2f& rhs) const
{
	return Vec2f( x + rhs.x , y + rhs.y );
}

Vec2f& Vec2f::operator+=(const Vec2f& rhs)
{
	return *this = *this + rhs;
}

Vec2f Vec2f::operator-( const Vec2f& rhs ) const
{
	return Vec2f( x - rhs.x,y - rhs.y );
}

Vec2f& Vec2f::operator-=( const Vec2f& rhs )
{
	return *this = *this - rhs;
}

Vec2f Vec2f::operator*(float rhs) const
{
	return Vec2f( x * rhs , y * rhs );
}

Vec2f& Vec2f::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Vec2f Vec2f::operator/( float rhs ) const
{
	return Vec2f( x / rhs,y / rhs );
}

Vec2f& Vec2f::operator/=( float rhs )
{
	return *this = *this / rhs;
}

bool Vec2f::operator==( const Vec2f& rhs ) const
{
	return x == rhs.x && y == rhs.y;
}

float Vec2f::getLength() const
{
	return std::sqrt( getLengthSq() );
}

float Vec2f::getLengthSq() const
{
	return x * x + y * y;
}

Vec2f& Vec2f::Nomalize()
{
	return *this = getNomalize();
}

Vec2f Vec2f::getNomalize() const
{
	const float len = getLengthSq();
	if ( len != 0.0f )
	{
		return *this * (1.0f / len);
	}
	return *this;
}

//-------------------------------------------------//

Vec2i::Vec2i( int x_in,int y_in )
	:
	x( x_in ),
	y( y_in )
{
}

Vec2i Vec2i::operator+( const Vec2i& rhs ) const
{
	return Vec2i( x + rhs.x,y + rhs.y );
}

Vec2i& Vec2i::operator+=( const Vec2i& rhs )
{
	return *this = *this + rhs;
}

Vec2i Vec2i::operator-( const Vec2i& rhs ) const
{
	return Vec2i( x - rhs.x,y - rhs.y );
}

Vec2i& Vec2i::operator-=( const Vec2i& rhs )
{
	return *this = *this - rhs;
}

Vec2i Vec2i::operator*( int rhs ) const
{
	return Vec2i( x * rhs,y * rhs );
}

Vec2i& Vec2i::operator*=( int rhs )
{
	return *this = *this * rhs;
}

Vec2i Vec2i::operator/( int rhs ) const
{
	return Vec2i( x / rhs,y / rhs );
}

Vec2i& Vec2i::operator/=( int rhs )
{
	return *this = *this / rhs;
}

bool Vec2i::operator==( const Vec2i& rhs ) const
{
	return x == rhs.x && y == rhs.y;
}

float Vec2i::getLength() const
{
	return float( std::sqrt( getLengthSq() ) );
}

float Vec2i::getLengthSq() const
{
	return float( x * x + y * y );
}

Vec2i& Vec2i::Nomalize()
{
	return *this = getNomalize();
}

Vec2i Vec2i::getNomalize() const
{
	const int len = int( getLengthSq() );
	if ( len != 0 )
	{
		return *this * ( 1 / len );
	}
	return *this;
}
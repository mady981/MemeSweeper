#include "HitBox.h"

HitBox::HitBox( float left_in,float right_in,float top_in,float bottem_in )
	:
	left( left_in ),
	right( right_in ),
	top( top_in ),
	bottem( bottem_in )
{
}

HitBox::HitBox( const Vector& topleft,const Vector& bottemright )
	:
	HitBox( topleft.x,bottemright.x,topleft.y,bottemright.y )
{
}

HitBox::HitBox( const Vector& topleft,float width,float height )
	:
	HitBox( topleft,topleft + Vector( width,height ) )
{
}

bool HitBox::isOverlappingWith( const HitBox& other ) const
{
	return right > other.left && left < other.right
		&& bottem > other.top && top < other.bottem;
}

bool HitBox::isOverlappingWith( const Vector& other ) const
{
	return right > other.x && left < other.x
		&& bottem > other.y && top < other.y;
}

HitBox HitBox::fromCenter( const Vector& center,float width,float height )
{
	const Vector half( width * 0.5f,height * 0.5f );
	return HitBox( center - half,center + half );
}

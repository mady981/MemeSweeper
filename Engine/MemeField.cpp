#include "MemeField.h"
#include <assert.h>

MemeField::MemeField( std::mt19937 rng )
{
	Vec2i init;
	for ( int n = 0; n < maxMemes; ++n )
	{
		do
		{
			std::uniform_int_distribution<int> xDist( 0,width );
			std::uniform_int_distribution<int> yDist( 0,height );
			init = { xDist( rng ),yDist( rng ) };
		} while ( tiles[init.y * width + init.x].getState() != Tile::State::Empty );
		tiles[init.y * width + init.x].Init();
	}
}

void MemeField::onTileClicked( const Vec2i& mousePos,Mouse::Event::Type met )
{
	assert( mousePos.x >= gridpos.x );
	assert( mousePos.x < width* SpriteCodex::tileSize + gridpos.x );
	assert( mousePos.y >= gridpos.x );
	assert( mousePos.y < height* SpriteCodex::tileSize + gridpos.y );
	Vec2i tile = { ( mousePos - gridpos ) / SpriteCodex::tileSize };
	if ( met == Mouse::Event::Type::LPress )
	{
		if ( tiles[tile.y * width + tile.x].getState() == Tile::State::Empty )
		{
			tiles[tile.y * width + tile.x].Reviel();
			RevielAround( tile );
			if ( tiles[tile.y * width + tile.x].gethasMeme() )
			{
				tiles[tile.y * width + tile.x].setState( Tile::State::Bombed );
				Fucked();
			}
		}
	}
	else if ( met == Mouse::Event::Type::RPress )
	{
		if ( tiles[tile.y * width + tile.x].getState() == Tile::State::Empty )
		{
			tiles[tile.y * width + tile.x].Flagg();
		}
		else if ( tiles[tile.y * width + tile.x].getState() == Tile::State::Flagged )
		{
			tiles[tile.y * width + tile.x].Empty();
		}
	}
}

int MemeField::CountMemes( const Vec2i& tilePos )
{
	int nMemes = 0;
	Vec2i topleft = { std::max( 0,tilePos.x - 1 ),std::max( 0,tilePos.y - 1 ) };
	Vec2i bottemright = { std::min( width - 1,tilePos.x + 1 ),std::min( height - 1,tilePos.y + 1 ) };
	for ( int x = topleft.x; x <= bottemright.x; ++x )
	{
		for ( int y = topleft.y; y <= bottemright.y; ++y )
		{
			if ( tiles[y * width + x].gethasMeme() )
			{
				++nMemes;
			}
		}
	}
	tiles[tilePos.y * width + tilePos.x].setnMemes( nMemes );
	return nMemes;
}

void MemeField::RevielAround( const Vec2i& tilePos )
{
	Vec2i topleft = { std::max( 0,tilePos.x - 1 ),std::max( 0,tilePos.y - 1 ) };
	Vec2i bottemright = { std::min( width - 1,tilePos.x + 1 ),std::min( height - 1,tilePos.y + 1 ) };
	for ( int x = topleft.x; x <= bottemright.x; ++x )
	{
		for ( int y = topleft.y; y <= bottemright.y; ++y )
		{
			if ( !tiles[y * width + x].gethasMeme() && CountMemes( Vec2i( tilePos.x,tilePos.y ) ) == 0 && tiles[y * width + x].getState() == Tile::State::Empty )
			{
				tiles[y * width + x].Reviel();
				RevielAround( Vec2i( x,y ) );
			}
		}
	}
}

void MemeField::Draw( SpriteCodex& sc,Graphics& gfx ) const
{
	gfx.DrawRectDim( gridpos,width * sc.tileSize,height * sc.tileSize,sc.baseColor );
	for ( int y = 0; y < height; ++y )
	{
		for ( int x = 0; x < width; ++x )
		{
			tiles[y * width + x].Draw( Vec2i( x,y ),gridpos,sc,gfx );
		}
	}
}

void MemeField::Fucked()
{
	for ( int y = 0; y < height; ++y )
	{
		for ( int x = 0; x < width; ++x )
		{
			if ( tiles[y * width + x].gethasMeme() )
			{
				tiles[y * width + x].setState( Tile::State::Bombed );
			}
		}
	}
	fucked = true;
}

void MemeField::WinCheck()
{
	int n = 0;
	for ( int y = 0; y < height; ++y )
	{
		for ( int x = 0; x < width; ++x )
		{
			n += tiles[y * width + x].Check();
		}
	}
	if ( n == maxMemes )
	{
		won = true;
	}
}

const int MemeField::getwidth() const
{
	return width;
}

const int MemeField::getheight() const
{
	return height;
}

const Vec2i MemeField::getgridpos() const
{
	return Vec2i( gridpos );
}

const bool MemeField::getFucked() const
{
	return fucked;
}

const bool MemeField::getWon() const
{
	return won;
}

bool MemeField::Tile::Init()
{
	if ( state == State::Empty )
	{
		hasMeme = true;
		return false;
	}
	return true;
}

void MemeField::Tile::Draw( const Vec2i& pos,const Vec2i& gridpos,SpriteCodex& sc,Graphics& gfx ) const
{
	switch ( state )
	{
	case MemeField::Tile::State::Bombed:
		sc.DrawTileBomb( pos * sc.tileSize + gridpos,gfx );
		break;
	case MemeField::Tile::State::Revield:
		sc.DrawTileNumber( pos * sc.tileSize + gridpos,nMemes,gfx );
		break;
	case MemeField::Tile::State::Flagged:
		sc.DrawTileFlag( pos * sc.tileSize + gridpos,gfx );
	case MemeField::Tile::State::Empty:
		sc.DrawTileButton( pos * sc.tileSize + gridpos,gfx );
		break;
	}
}

int MemeField::Tile::Check()
{
	if ( hasMeme && state == State::Flagged )
	{
		return 1;
	}
	if ( !hasMeme && state == State::Flagged )
	{
		return -1;
	}
	return 0;
}

MemeField::Tile::State MemeField::Tile::Reviel()
{
	state = State::Revield;
	return State( state );
}

MemeField::Tile::State MemeField::Tile::Flagg()
{
	state = State::Flagged;
	return State( state );
}

MemeField::Tile::State MemeField::Tile::Empty()
{
	state = State::Empty;
	return State( state );
}

const MemeField::Tile::State MemeField::Tile::getState() const
{
	return State( state );
}

MemeField::Tile::State MemeField::Tile::setState( const State& state_in )
{
	state = state_in;
	return State( state );
}

const bool MemeField::Tile::gethasMeme() const
{
	return hasMeme;
}

int MemeField::Tile::setnMemes( const int nMemes_in )
{
	nMemes = nMemes_in;
	return nMemes;
}

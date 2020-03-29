#pragma once
#include "Vector.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Mouse.h"
#include <random>

class MemeField
{
private:
	class Tile
	{
	public:
		enum class State
		{
			Empty,
			Flagged,
			Revield,
			Bombed
		};
	public:
		bool Init();
		void Draw( const Vec2i& pos,const Vec2i& gridpos,SpriteCodex& sc,Graphics& gfx ) const;
		int Check();
		State Reviel();
		State Flagg();
		State Empty();
		const State getState() const;
		State setState( const State& state_in );
		const bool gethasMeme() const;
		int setnMemes( const int nMemes_in );
	private:
		bool hasMeme = false;
		int nMemes = 0;
		State state = State::Empty;
	};
public:
	MemeField( std::mt19937 rng );
	void onTileClicked( const Vec2i& mousePos,Mouse::Event::Type met );
	int CountMemes( const Vec2i& tilePos );
	void RevielAround( const Vec2i& tilePos );
	void Draw( SpriteCodex& sc,Graphics& gfx ) const;
	void Fucked();
	void WinCheck();
	const int getwidth() const;
	const int getheight() const;
	const Vec2i getgridpos() const;
	const bool getFucked() const;
	const bool getWon() const;
private:
	static constexpr int width = 20;
	static constexpr int height = 15;
	static constexpr int maxMemes = 20;
	const Vec2i gridpos = { 60,60 };
	Tile tiles[width * height];
	bool fucked = false;
	bool won = false;
};

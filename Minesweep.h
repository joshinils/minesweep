#ifndef MINESWEEP_H
#define MINESWEEP_H

#include "olcPixelGameEngine.h"
#include "Tile.h"
#include <array>

class Minesweep : public olc::PixelGameEngine
{
	std::vector<std::vector<Tile>> _playField;

public:
	Minesweep(size_t nTx, size_t nTy)
		: _playField(nTx, std::vector<Tile>(nTx, Tile(-1,-1)))
	{
		sAppName = "Minesweep";
        int color = Tile::DisplayNum::Nothing;
		for (size_t i = 0; i < nTx; i++)
		{
			for (size_t j = 0; j < nTy; j++)
			{
				_playField.at(i).at(j) = Tile(i*Tile::WIDTH + Tile::BORDER, j*Tile::HEIGHT + Tile::BORDER);
				_playField.at(i).at(j).setNum(color++);
			}
		}
	}

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		return true;
	}

	void drawTiles()
	{
		for (auto& v:_playField)
		{
			for (auto& t:v)
			{
				t.draw();
			}
		}
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		drawTiles();
		std::cout << std::endl;

		// check leftMouseButton
		if (GetMouse(0).bPressed)
		{
			std::cout << "Mouse(0).bPressed" << std::endl;
		}
		if (GetMouse(0).bHeld)
		{
			std::cout << "Mouse(0).bHeld" << std::endl;
		}
		if (GetMouse(0).bReleased)
		{
			std::cout << "Mouse(0).bReleased" << std::endl;
			size_t x = ( GetMouseX() - Tile::BORDER) / Tile::WIDTH ;
			size_t y = ( GetMouseY() - Tile::BORDER) / Tile::HEIGHT ;
			_playField.at(x).at(y).uncover();
		}

		// check rightMouseButton
		if (GetMouse(1).bPressed) // then also held, start of press
		{
			std::cout << "Mouse(1).bPressed" << std::endl;
		}
		if (GetMouse(1).bHeld) // if not pressed continued holding down
		{
			std::cout << "Mouse(1).bHeld" << std::endl;
		}
		if (GetMouse(1).bReleased) // not held, or ppressed, stopped pressing
		{
			std::cout << "Mouse(1).bReleased" << std::endl;
			size_t x = ( GetMouseX() - Tile::BORDER) / Tile::WIDTH ;
			size_t y = ( GetMouseY() - Tile::BORDER) / Tile::HEIGHT ;
			_playField.at(x).at(y).toggleFlagged();
		}

		//	std::cout << std::endl;
		return true;
	}

	static Minesweep& instance(size_t nTx = 0, size_t nTy = 0)
	{
		static Minesweep _ms(nTx, nTy);
		return _ms;
	}
};

#endif // MINESWEEP_H
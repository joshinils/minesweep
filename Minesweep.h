#ifndef MINESWEEP_H
#define MINESWEEP_H

#include "olcPixelGameEngine.h"

#include <iostream>

#include "Tile.h"
#include <array>

class Minesweep : public olc::PixelGameEngine
{
	std::vector<std::vector<Tile>> _playField;

    void initTiles()
    {
        for (unsigned int i = 0; i < _playField.size(); i++)
        {
            for (unsigned int j = 0; j < _playField.at(0).size(); j++)
            {
                _playField.at(i).at(j) = Tile(i*Tile::WIDTH + Tile::BORDER, j*Tile::HEIGHT + Tile::BORDER);

                int r = std::rand();
                if (r % 8 == 0)
                    _playField.at(i).at(j).placeMine();
                _playField.at(i).at(j).setNum(Tile::DisplayNum::Nothing);
            }
        }
    }

    void initNumbers()
    {
        for (unsigned int spalte = 0; spalte < _playField.size(); spalte++)
        {
            for (unsigned int zeile = 0; zeile < _playField.at(0).size(); zeile++)
            {
                int neighbouringMines = 0;

                // above middle
                if (zeile > 0)
                    neighbouringMines += _playField.at(spalte).at(zeile -1).isMine();

                // above left
                if (zeile > 0 && spalte > 0)
                    neighbouringMines += _playField.at(spalte -1).at(zeile -1).isMine();

                // left
                if (spalte > 0)
                    neighbouringMines += _playField.at(spalte -1).at(zeile).isMine();

                // below left
                if (_playField.at(0).size() -1 > zeile && spalte > 0)
                    neighbouringMines += _playField.at(spalte-1).at(zeile +1).isMine();

                // below middle
                if (_playField.at(0).size() -1 > zeile)
                    neighbouringMines += _playField.at(spalte).at(zeile +1).isMine();

                // below right
                if (_playField.at(0).size() -1 > zeile &&_playField.size() -1 > spalte)
                    neighbouringMines += _playField.at(spalte +1).at(zeile +1).isMine();

                // right
                if (_playField.size() -1 > spalte)
                    neighbouringMines += _playField.at(spalte +1).at(zeile).isMine();

                // above right
                if (_playField.size() -1 > spalte && zeile > 0)
                    neighbouringMines += _playField.at(spalte +1).at(zeile -1).isMine();

                _playField.at(spalte).at(zeile).setNum(neighbouringMines);
            }
        }
    }

    bool _gameLost = false;

    void loose()
    {
        _gameLost = true;
        for (unsigned int spalte = 0; spalte < _playField.size(); spalte++)
        {
            for (unsigned int zeile = 0; zeile < _playField.at(0).size(); zeile++)
            {
                _playField.at(zeile).at(spalte).doShowMine();
            }
        }
    }

public:
	Minesweep(size_t nTx, size_t nTy)
		: _playField(nTx, std::vector<Tile>(nTy, Tile( -1, -1)))
	{
		sAppName = "Minesweep";
        initTiles();
        initNumbers();
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
        if (_gameLost)
        {
            static bool drawOneLastTime = true;
            if (drawOneLastTime)
                drawOneLastTime = false;
            else
                return true;
        }

		drawTiles();
		std::cout << std::endl;

		// check leftMouseButton
		if (GetMouse(0).bHeld)
		{
			std::cout << "Mouse(0).bHeld" << std::endl;
		}
		if (GetMouse(0).bReleased)
		{
			std::cout << "Mouse(0).bReleased" << std::endl;
			size_t x = ( GetMouseX() - Tile::BORDER) / Tile::WIDTH ;
			size_t y = ( GetMouseY() - Tile::BORDER) / Tile::HEIGHT ;
            if (_playField.at(x).at(y).isMine())
                loose();
            else
                _playField.at(x).at(y).uncover();
		}

		// check rightMouseButton
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
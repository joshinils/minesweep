#ifndef MINESWEEP_H
#define MINESWEEP_H

#include "olcPixelGameEngine.h"

#include <iostream>

#include "Tile.h"
#include <array>

class Minesweep : public olc::PixelGameEngine
{
    std::vector<std::pair<unsigned int, unsigned int>> _heldPos;
	std::vector<std::vector<Tile>> _playField;
    bool _gameLost = false;

    void initTiles();
    void initNumbers();
    void loose();
    bool OnUserUpdate(float fElapsedTime) override;

    // Called once at the start, so create things here
    bool OnUserCreate() override;

    void uncover(size_t x, size_t y);

    size_t _nTx;
    size_t _nTy;

    Minesweep(size_t nTx, size_t nTy);

public:
    void drawTiles();

    static Minesweep& instance(size_t nTx = 0, size_t nTy = 0);
};

#endif // MINESWEEP_H
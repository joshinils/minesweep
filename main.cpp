#include <iostream>

#include "Minesweep.h"
#include "Tile.h"

int main()
{
    uint32_t nTilesX = 10;
    uint32_t nTilesY = 10;

    uint32_t displaySizeX = nTilesX * Tile::WIDTH  + Tile::BORDER*2 +1; // +1 for linewidth of tile itself
    uint32_t displaySizeY = nTilesX * Tile::HEIGHT + Tile::BORDER*2 +1;

	Minesweep& game = Minesweep::instance(nTilesX, nTilesY);
	if (game.Construct(displaySizeX, displaySizeY, 1u, 1u))
		game.Start();

	return 0;
}

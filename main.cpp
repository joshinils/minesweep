#include <iostream>

#include "Tile.h"
#include "Minesweep.h"

int main()
{
	size_t nTilesX = 10;
	size_t nTilesY = 10;

	size_t displaySizeX = nTilesX * Tile::WIDTH  + Tile::BORDER*2 +1; // +1 for linewidth of tile itself
	size_t displaySizeY = nTilesX * Tile::HEIGHT + Tile::BORDER*2 +1;

	Minesweep& game = Minesweep::instance(nTilesX, nTilesY);
	if (game.Construct(displaySizeX, displaySizeY, 1, 1))
		game.Start();

	return 0;
}

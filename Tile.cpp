#include "Tile.h"
#include "Minesweep.h"

Tile::Tile(size_t x, size_t y)
	: _x(x)
	, _y(y)
	, _isMine(false)
	, _uncovered(false)
	, _flagged(false)
{ }

void Tile::draw()
{
	Minesweep& ms = Minesweep::instance();
	if(_uncovered)
		ms.FillRect(_x, _y, Tile::WIDTH, Tile::HEIGHT, olc::Pixel(129, 129, 129, 255));
	else
		ms.FillRect(_x, _y, Tile::WIDTH, Tile::HEIGHT, olc::Pixel(189, 189, 189, 255) );

	if(_flagged)
		ms.FillCircle(_x + Tile::WIDTH/2, _y + Tile::HEIGHT/2, (Tile::WIDTH + Tile::HEIGHT)/6, olc::RED);

	ms.DrawRect(_x, _y, Tile::WIDTH -1, Tile::HEIGHT -1, olc::VERY_DARK_GREY );

	ms.DrawString(_x, _x, std::to_string(_numToDisplay), olc::GREEN);
}

void Tile::uncover()
{
	_uncovered = true;
	_flagged = false;
	draw();
}

void Tile::cover()
{
	_uncovered = false;
	draw();
}

void Tile::flag()
{
	_flagged = !_uncovered;
	draw();
}

void Tile::unflag()
{
	_flagged = false;
}

void Tile::toggleFlagged()
{
	if(!_uncovered)
		_flagged = !_flagged;
}

void Tile::setNum(DisplayNum d)
{
	_numToDisplay = d;
}


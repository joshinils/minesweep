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

    olc::Pixel numColor = olc::BLACK;
    switch (_numToDisplay)
    {
    case Tile::DisplayNum::One:   numColor = olc::Pixel(  0,   0, 255); break;
    case Tile::DisplayNum::Two:   numColor = olc::Pixel(  0, 123,   0); break;
    case Tile::DisplayNum::Three: numColor = olc::Pixel(255,   0,   0); break;
    case Tile::DisplayNum::Four:  numColor = olc::Pixel(  0,   0, 123); break;
    case Tile::DisplayNum::Five:  numColor = olc::Pixel(123,   0,   0); break;
    case Tile::DisplayNum::Six:   numColor = olc::Pixel(  0, 123, 123); break;
    case Tile::DisplayNum::Seven: numColor = olc::Pixel(123,   0, 123); break;
    case Tile::DisplayNum::Eight: numColor = olc::Pixel(123, 123, 123); break;
    default: numColor = olc::YELLOW; break;
    }
    ms.DrawString(_x, _y, std::to_string(_numToDisplay), numColor);
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

void Tile::setNum(int i)
{
    i %= 10;
       
    switch (i)
    {
    case Tile::DisplayNum::One:   _numToDisplay = Tile::DisplayNum::One;    break;
    case Tile::DisplayNum::Two:   _numToDisplay = Tile::DisplayNum::Two;    break;
    case Tile::DisplayNum::Three: _numToDisplay = Tile::DisplayNum::Three;  break;
    case Tile::DisplayNum::Four:  _numToDisplay = Tile::DisplayNum::Four;   break;
    case Tile::DisplayNum::Five:  _numToDisplay = Tile::DisplayNum::Five;   break;
    case Tile::DisplayNum::Six:   _numToDisplay = Tile::DisplayNum::Six;    break;
    case Tile::DisplayNum::Seven: _numToDisplay = Tile::DisplayNum::Seven;  break;
    case Tile::DisplayNum::Eight: _numToDisplay = Tile::DisplayNum::Eight;  break;
    default:                      _numToDisplay = Tile::DisplayNum::Nothing;break;
    }
}

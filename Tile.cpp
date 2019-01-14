#include "Minesweep.h"

#include "Tile.h"


//olc::Sprite Tile::_lid(Tile::WIDTH, Tile::HEIGHT);

const olc::Pixel Tile::BACKGROUND = olc::Pixel(123, 123, 123);

Tile::Tile(unsigned int x, unsigned int y)
	: _x(x)
	, _y(y)
	, _isMine(false)
	, _uncovered(false)
	, _isFlagged(false)
    , _showMine(false)
    , _isHeldDown(false)
{
    //static bool lidExists = false;
    //if (lidExists)
    //    return;
    //lidExists = true;

    ////fill lid once:

    //olc::Pixel backgroundColor(123, 123, 123);
    //for (size_t i = 0; i < Tile::WIDTH; i++)
    //{
    //    for (size_t j = 0; j < Tile::HEIGHT; j++)
    //    {
    //        _lid.SetPixel(i, j, backgroundColor);
    //    }
    //}

    //olc::Pixel upper(170, 170, 170);

    //// upper
    //for (size_t i = 2; i < Tile::WIDTH -1; ++i)
    //{
    //    _lid.SetPixel(i, 0, upper);
    //    if (i == Tile::WIDTH - 2)
    //        break;
    //    _lid.SetPixel(i, 1, upper);
    //}

    //// left
    //for (size_t i = 0; i < Tile::HEIGHT -1; ++i)
    //{
    //    _lid.SetPixel(0, i, upper);
    //    if (i == Tile::HEIGHT - 2)
    //        break;
    //    _lid.SetPixel(1, i, upper);
    //}


    //olc::Pixel lower( 82,  82,  82);

    //// right
    //for (size_t i = 1; i < Tile::HEIGHT -2; ++i)
    //{
    //    _lid.SetPixel(Tile::WIDTH - 1, i, lower);

    //    if (i == 1)
    //        continue;
    //    _lid.SetPixel(Tile::WIDTH - 2, i, lower);
    //}

    //// bottom
    //for (size_t i = 1; i < Tile::WIDTH; ++i)
    //{
    //    _lid.SetPixel(i, Tile::HEIGHT - 1, lower);

    //    if (i == 1)
    //        continue;
    //    _lid.SetPixel(i, Tile::HEIGHT - 2, lower);
    //}
}

void Tile::draw()
{
	Minesweep& ms = Minesweep::instance();

    if (_isKilled)
    {
//        ms.FillRect(_x, _y, Tile::WIDTH, Tile::HEIGHT, olc::BLACK);
        return;
    }

    // background
    //if (_isMine) // debugging
    //    ms.FillRect(_x, _y, Tile::WIDTH, Tile::HEIGHT, olc::Pixel(255,0,0,100));

    if (!_uncovered && !_isHeldDown)
    {
        unsigned int w = Tile::WIDTH - 1;
        unsigned int h = Tile::HEIGHT - 1;

        // top
        ms.DrawLine(_x        , _y        , _x + w - 1, _y        , olc::Pixel(170, 170, 170));
        ms.DrawLine(_x     + 1, _y     + 1, _x + w - 2, _y    + 1 , olc::Pixel(170, 170, 170));

        // left
        ms.DrawLine(_x        , _y        , _x        , _y + h - 1, olc::Pixel(170, 170, 170));
        ms.DrawLine(_x     + 1, _y     + 1, _x     + 1, _y + h - 2, olc::Pixel(170, 170, 170));

        // right
        ms.DrawLine(_x + w    , _y + 1    , _x + w    , _y + h    , olc::Pixel( 82,  82,  82));
        ms.DrawLine(_x + w - 1, _y + 2    , _x + w - 1, _y + h    , olc::Pixel( 82,  82,  82));

        // bottom
        ms.DrawLine(_x     + 1, _y + h    , _x + w    , _y + h    , olc::Pixel( 82,  82,  82));
        ms.DrawLine(_x     + 2, _y + h - 1, _x + w    , _y + h - 1, olc::Pixel( 82,  82,  82));

        // background
        ms.FillRect(_x+2, _y+2, Tile::WIDTH-4, Tile::HEIGHT-4, Tile::BACKGROUND);

        // top right
        ms.Draw(_x + w    , _y    , Tile::BACKGROUND);
        ms.Draw(_x + w - 1, _y + 1, Tile::BACKGROUND);

        // bottom left
        ms.Draw(_x    , _y + h    , Tile::BACKGROUND);
        ms.Draw(_x + 1, _y + h - 1, Tile::BACKGROUND);
    }
    else
    {
        ms.FillRect(_x +1, _y+1, Tile::WIDTH - 1, Tile::HEIGHT - 1, Tile::BACKGROUND);
    }

    if(_uncovered || _isHeldDown)
    {
        _isHeldDown = false;
        unsigned int w = Tile::WIDTH - 1;
        unsigned int h = Tile::HEIGHT - 1;

        // top
        ms.DrawLine(_x        , _y        , _x + w    , _y        , olc::Pixel( 82,  82,  82));

        // left
        ms.DrawLine(_x        , _y        , _x        , _y + h    , olc::Pixel( 82,  82,  82));
    }

    // draw flag circle
    if (_isFlagged)
    {
        uint8_t r = (Tile::WIDTH + Tile::HEIGHT) / 6-1;
        unsigned int y1 = 100;
        for (uint8_t i = 0; i < r; i++)
        {
            ms.FillCircle(_x + Tile::WIDTH / 2, _y + Tile::HEIGHT / 2, r -i , olc::Pixel((255 - y1)*i/r + y1, 0, 0));
        }
    }

    olc::Pixel numColor = olc::BLACK;
    switch (_numToDisplay)
    {
    case Tile::DisplayNum::Nothing:numColor = olc::Pixel(  0,   0,   0); break;
    case Tile::DisplayNum::One:    numColor = olc::Pixel(  0,   0, 255); break;
    case Tile::DisplayNum::Two:    numColor = olc::Pixel(  0, 123,   0); break;
    case Tile::DisplayNum::Three:  numColor = olc::Pixel(255,   0,   0); break;
    case Tile::DisplayNum::Four:   numColor = olc::Pixel(  0,   0, 123); break;
    case Tile::DisplayNum::Five:   numColor = olc::Pixel(123,   0,   0); break;
    case Tile::DisplayNum::Six:    numColor = olc::Pixel(  0, 123, 123); break;
    case Tile::DisplayNum::Seven:  numColor = olc::Pixel(123,   0, 123); break;
    case Tile::DisplayNum::Eight:  numColor = olc::Pixel(123, 123, 123); break;
    default: numColor = olc::YELLOW; break;
    }

    // display number of neighbors
    if(!_isMine
        && _uncovered
        && _numToDisplay != Tile::DisplayNum::Nothing)
        ms.DrawString(_x +4*SCALE, _y +4*SCALE, std::to_string(_numToDisplay), numColor, SCALE);

    // draw mine
    if(_showMine && _isMine)
        {
            unsigned int r = (Tile::WIDTH + Tile::HEIGHT) / 8;
            unsigned int y1 = 200;
            for (size_t i = 0; i < r; i++)
            {
                uint8_t c = uint8_t(255 -((255 - y1)*i / r + y1));
                ms.FillCircle(_x + Tile::WIDTH / 2, _y + Tile::HEIGHT / 2, int32_t(r -i) , olc::Pixel(c, c, c, 200));
            }
        }

}

void Tile::uncover()
{
    if (_isKilled)
        return;

    if(_isFlagged == false)
    	_uncovered = true;
	draw();
}

void Tile::cover()
{
    if (_isKilled)
        return;

	_uncovered = false;
	draw();
}

bool Tile::isCovered()
{
    if (_isKilled)
        return false;

    return !_uncovered;
}

void Tile::flag()
{
    if (_isKilled)
        return;

	_isFlagged = !_uncovered;
	draw();
}

void Tile::unflag()
{
	_isFlagged = false;
}

void Tile::toggleFlagged()
{
	if(!_uncovered)
		_isFlagged = !_isFlagged;
}

bool Tile::isFlagged()
{
    if (_isKilled)
        return false;

    return _isFlagged;
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

Tile::DisplayNum Tile::getNum()
{
    return _numToDisplay;
}

void Tile::placeMine()
{
    if (_isKilled)
        return;

    _isMine = true;
}

void Tile::doShowMine()
{
    _showMine = true;
}

bool Tile::isMine()
{
    if (_isKilled)
        return false;
    return _isMine;
}

void Tile::holdDown()
{
    if (_isKilled)
        return;

    _isHeldDown = true;
}

bool Tile::isHeld()
{
    if (_isKilled)
        return false;

    return _isHeldDown;
}

void Tile::kill()
{
    _isKilled = true;
}

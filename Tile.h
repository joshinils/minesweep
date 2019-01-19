#ifndef TILE_H
#define TILE_H

#include "olcPixelGameEngine.h"

class Tile
{
public:
	enum DisplayNum
	{
		Nothing = 0,
		One = 1,
		Two = 2,
		Three = 3,
		Four = 4,
		Five = 5,
		Six = 6,
		Seven = 7,
		Eight = 8,
		Nine = 9,
	};

private:
	unsigned int _x, _y;
	bool _isMine;
	bool _uncovered;
	bool _isFlagged;
	DisplayNum _numToDisplay;
    bool _showMine;
//    static olc::Sprite _lid;
    bool _isHeldDown = false;
    bool _isKilled = false;

public:

	const static unsigned int SCALE = 1;
    const static unsigned int WIDTH = 16 * SCALE;
    const static unsigned int HEIGHT = 16 * SCALE;
	const static unsigned int BORDER = 4 * SCALE;
    const static olc::Pixel BACKGROUND;

	Tile() = delete;
	Tile(unsigned int x, unsigned int y);
    ~Tile()
    {
//        std::cout << __FUNCTION__ << std::endl;
    };

	void draw();

    void uncover();
	void cover();
    bool isCovered();

	void flag();
	void unflag();
	void toggleFlagged();
    bool isFlagged();

	void setNum(DisplayNum d);
    void setNum(int i);
    DisplayNum getNum();

    void placeMine();
    void doShowMine();

    bool isMine();

    void holdDown();
    bool isHeld();

    void kill();
};

#endif // TILE_H

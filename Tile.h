#ifndef TILE_H
#define TILE_H

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
	bool _flagged;
	DisplayNum _numToDisplay;
    bool _showMine;

public:

	const static unsigned int SCALE = 1;
    const static unsigned int WIDTH = 16 * SCALE;
    const static unsigned int HEIGHT = 16 * SCALE;
	const static unsigned int BORDER = 4 * SCALE;

	Tile() = delete;
	Tile(unsigned int x, unsigned int y);
	~Tile() = default;

	void draw();
	void uncover();
	void cover();
	void flag();
	void unflag();
	void toggleFlagged();

	void setNum(DisplayNum d);
    void setNum(int i);

    void placeMine();
    void doShowMine();

    bool isMine();

};

#endif // TILE_H
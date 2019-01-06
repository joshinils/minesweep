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
		eight = 8,
		Nine = 9,
	};

private:
	size_t _x, _y;
	bool _isMine;
	bool _uncovered;
	bool _flagged;
	DisplayNum _numToDisplay;

public:

	static const size_t WIDTH = 16*2;
	static const size_t HEIGHT = 16*2;
	static const size_t BORDER = 4*2;

	Tile() = delete;
	Tile(size_t x, size_t y);
	~Tile() = default;

	void draw();
	void uncover();
	void cover();
	void flag();
	void unflag();
	void toggleFlagged();

	void setNum(DisplayNum d);
};

#endif // TILE_H
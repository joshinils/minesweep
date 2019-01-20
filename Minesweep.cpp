#include "Minesweep.h"

void Minesweep::initTiles()
{
    for (unsigned int i = 0; i < _nTx; i++)
    {
        std::vector<Tile> nVec;
        for (unsigned int j = 0; j < _nTy; j++)
        {
            Tile t(i*Tile::WIDTH + Tile::BORDER, j*Tile::HEIGHT + Tile::BORDER);
            nVec.push_back(t);

            int r = std::rand();
            if (r % 8 == 0)
                nVec.at(j).placeMine();
            nVec.at(j).setNum(Tile::DisplayNum::Nothing);
            int d = (int)ceil(pow((_nTx/2 - i)*(_nTx/2 - i) + (_nTy/2 - j)*(_nTy/2 - j), .5));

            for (int in = 0; in < d; ++in)
            {
                r = std::rand();
                if (r % 101 == 0)
                {
                    // currently dont kill
                    //nVec.at(j).kill();
                    break;
                }
            }
        }
        _playField.push_back(nVec);
    }

    initNumbers();
}

void Minesweep::initNumbers()
{
    for (unsigned int spalte = 0; spalte < _playField.size(); spalte++)
    {
        for (unsigned int zeile = 0; zeile < _playField.at(0).size(); zeile++)
        {
            int neighbouringMines = 0;

            // above middle
            if (zeile > 0)
                neighbouringMines += _playField.at(spalte).at(zeile - 1).isMine();

            // above left
            if (zeile > 0 && spalte > 0)
                neighbouringMines += _playField.at(spalte - 1).at(zeile - 1).isMine();

            // left
            if (spalte > 0)
                neighbouringMines += _playField.at(spalte - 1).at(zeile).isMine();

            // below left
            if (_playField.at(0).size() - 1 > zeile && spalte > 0)
                neighbouringMines += _playField.at(spalte - 1).at(zeile + 1).isMine();

            // below middle
            if (_playField.at(0).size() - 1 > zeile)
                neighbouringMines += _playField.at(spalte).at(zeile + 1).isMine();

            // below right
            if (_playField.at(0).size() - 1 > zeile &&_playField.size() - 1 > spalte)
                neighbouringMines += _playField.at(spalte + 1).at(zeile + 1).isMine();

            // right
            if (_playField.size() - 1 > spalte)
                neighbouringMines += _playField.at(spalte + 1).at(zeile).isMine();

            // above right
            if (_playField.size() - 1 > spalte && zeile > 0)
                neighbouringMines += _playField.at(spalte + 1).at(zeile - 1).isMine();

            _playField.at(spalte).at(zeile).setNum(neighbouringMines);
        }
    }
}

void Minesweep::loose()
{
    _gameLost = true;
    for (unsigned int spalte = 0; spalte < _playField.size(); spalte++)
    {
        for (unsigned int zeile = 0; zeile < _playField.at(0).size(); zeile++)
        {
            _playField.at(spalte).at(zeile).doShowMine();
        }
    }
}


bool Minesweep::_middleStillHeld(false);

Minesweep::Minesweep(size_t nTx, size_t nTy)
  //  : _playField(nTx, std::vector<Tile>(nTy, Tile(-1, -1)))
    : _nTx(nTx)
    , _nTy(nTy)
{
    sAppName = "Minesweep";
}

void Minesweep::drawTiles()
{
    olc::Pixel backgroundColor(123, 123, 123);
//    Clear(backgroundColor);
    for (auto& v : _playField)
    {
        for (auto& t : v)
        {
            t.draw();
        }
    }
}

int Minesweep::aiMiddleAll()
{
    for (size_t i = 0; i < _nTx; i++)
    {
        for (size_t j = 0; j < _nTy; j++)
        {
            _middleStillHeld = true;
            middleClick(i, j);
            Minesweep::performLogic(true);
        }
    }
    return 0;
}

olc::HWButton Minesweep::GetMouse(uint32_t b)
{
    olc::HWButton hw = olc::PixelGameEngine::GetMouse(b);

    if(    b == Minesweep::MouseButton::middle
        && ( (    olc::PixelGameEngine::GetMouse(Minesweep::MouseButton::left  ).bHeld
               && olc::PixelGameEngine::GetMouse(Minesweep::MouseButton::right ).bHeld )
             || olc::PixelGameEngine::GetMouse(Minesweep::MouseButton::middle ).bHeld)
      )
    {
        hw.bHeld = true;
    }
    else if(b == Minesweep::MouseButton::middle)
    {
        hw.bHeld = false;
    }

    return hw;
}

void Minesweep::leftClick(size_t x, size_t y)
{
    if (_playField.at(x).at(y).isMine())
        loose();
    else
        uncover(x, y);
}

void Minesweep::rightClick(size_t x, size_t y)
{
    _playField.at(x).at(y).toggleFlagged();
}

void Minesweep::middleClick(size_t x, size_t y)
{
    _heldPos.clear();

    //middle
    _playField.at(x).at(y).holdDown();
    _heldPos.push_back(std::make_pair(x, y));

    // and surrounding
    // above middle
    if (y > 0)
    {
        _playField.at(x).at(y - 1).holdDown();
        _heldPos.push_back(std::make_pair(x, y - 1));
    }

    // above left
    if (y > 0 && x > 0)
    {
        _playField.at(x - 1).at(y - 1).holdDown();
        _heldPos.push_back(std::make_pair(x - 1, y - 1));
    }

    // left
    if (x > 0)
    {
        _playField.at(x - 1).at(y).holdDown();
        _heldPos.push_back(std::make_pair(x - 1, y));
    }

    // below left
    if (_playField.at(0).size() - 1 > y && x > 0)
    {
        _playField.at(x - 1).at(y + 1).holdDown();
        _heldPos.push_back(std::make_pair(x - 1, y + 1));
    }

    // below middle
    if (_playField.at(0).size() - 1 > y)
    {
        _playField.at(x).at(y + 1).holdDown();
        _heldPos.push_back(std::make_pair(x, y + 1));
    }

    // below right
    if (_playField.at(0).size() - 1 > y &&_playField.size() - 1 > x)
    {
        _playField.at(x + 1).at(y + 1).holdDown();
        _heldPos.push_back(std::make_pair(x + 1, y + 1));
    }

    // right
    if (_playField.size() - 1 > x)
    {
        _playField.at(x + 1).at(y).holdDown();
        _heldPos.push_back(std::make_pair(x + 1, y));
    }

    // above right
    if (_playField.size() - 1 > x && y > 0)
    {
        _playField.at(x + 1).at(y - 1).holdDown();
        _heldPos.push_back(std::make_pair(x + 1, y - 1));
    }
}

bool Minesweep::OnUserUpdate(float fElapsedTime)
{
    if (_gameLost)
    {
        static bool drawOneLastTime = true;
        if (drawOneLastTime)
        {
            drawOneLastTime = false;
        }
        else
        {
            return true;
        }
    }


    olc::HWButton space = olc::PixelGameEngine::GetKey(olc::Key::SPACE);
    if (true ||space.bReleased)
    {
        aiMiddleAll();
    }

    drawTiles();
    drawTiles();

    return performLogic();
}

// Called once at the start, so create things here
bool Minesweep::OnUserCreate()
{
    initTiles();
    leftClick(14,10); // to get the ai started
    return true;
}

bool Minesweep::performLogic(bool fremdaufruf /* = false */)
{
    size_t mousePointedX = (GetMouseX() - Tile::BORDER) / Tile::WIDTH;
    size_t mousePointedY = (GetMouseY() - Tile::BORDER) / Tile::HEIGHT;

    //    static bool _middleStillHeld = false;
    // is mousepos legal?
    if (mousePointedX >= 0 && mousePointedX < _playField.size()&&
        mousePointedY >= 0 && mousePointedY < _playField.at(0).size() )
    {
        bool isLeft_Held = GetMouse(Minesweep::MouseButton::left).bHeld;
        bool isRightHeld = GetMouse(Minesweep::MouseButton::right).bHeld;
        bool isMidleHeld = GetMouse(Minesweep::MouseButton::midle).bHeld;

        bool isLeft_Rels = GetMouse(Minesweep::MouseButton::left).bReleased;
        bool isRightRels = GetMouse(Minesweep::MouseButton::right).bReleased;
        bool isMidleRels = GetMouse(Minesweep::MouseButton::midle).bReleased;

        if( isMidleHeld
            ||(   _middleStillHeld && isLeft_Held
                || _middleStillHeld && isRightHeld )
            )
        {
            _middleStillHeld = true;
            middleClick(mousePointedX, mousePointedY);
        }

        if(     _middleStillHeld
            && !(isRightHeld || isLeft_Held || isMidleHeld)
            &&  (isRightRels || isLeft_Rels /* || isMidleRels, this is the bit that shall be remembered */ || fremdaufruf))
        {
            _middleStillHeld = false;

            if (_heldPos.size() > 0 && !_playField.at(_heldPos.at(0).first).at(_heldPos.at(0).second).isCovered())
            {
                bool dontContinue = false;
                int minesLeft = 0;
                for (unsigned int i = 0; i < _heldPos.size(); i++)
                {
                    Tile& t = _playField.at(_heldPos.at(i).first).at(_heldPos.at(i).second);

                    // is it wrongly flagged?
                    if (t.isFlagged() && !t.isMine())
                        loose();

                    if (t.isMine() && !t.isFlagged())
                    {
                        dontContinue = true;
                    }

                    if (t.isMine())
                        ++minesLeft;
                }

                for (unsigned int i = 0; i < _heldPos.size(); i++)
                {
                    if (dontContinue)
                        break;

                    Tile& t = _playField.at(_heldPos.at(i).first).at(_heldPos.at(i).second);

                    if (t.isFlagged())
                        continue;

                    uncover(_heldPos.at(i).first, _heldPos.at(i).second);
                }
                return true;
            }

            _heldPos.clear();
        }
        else if (_middleStillHeld == false)
        {
            // left is released, right is not released and not held
            if (isLeft_Rels && !isRightRels && !isRightHeld)
            {
                leftClick(mousePointedX, mousePointedY);
            }
            else if (!isLeft_Rels && isRightRels && !isLeft_Held)
            {
                rightClick(mousePointedX, mousePointedY);
            }
        }
    }
    //    //	std::cout << std::endl;
    return true;
}

void Minesweep::uncover(size_t x, size_t y)
{
    Tile& t = _playField.at(x).at(y);
    if(t.isMine() || !t.isCovered())
        return;

    t.uncover();

    // if no number, uncover all neighbors
    if (t.getNum() == Tile::DisplayNum::Nothing)
    {
        // above middle
        if (y > 0)
            uncover(x, y - 1);

        // above left
        if (y > 0 && x > 0)
            uncover(x - 1, y - 1);

        // left
        if (x > 0)
            uncover(x - 1, y);

        // below left
        if (_playField.at(0).size() - 1 > y && x > 0)
            uncover(x - 1, y + 1);

        // below middle
        if (_playField.at(0).size() - 1 > y)
            uncover(x, y + 1);

        // below right
        if (_playField.at(0).size() - 1 > y &&_playField.size() - 1 > x)
            uncover(x + 1, y + 1);

        // right
        if (_playField.size() - 1 > x)
            uncover(x + 1, y);

        // above right
        if (_playField.size() - 1 > x && y > 0)
            uncover(x + 1, y - 1);
    }
}


Minesweep& Minesweep::instance(size_t nTx, size_t nTy)
{
    static Minesweep _ms(nTx, nTy);
    return _ms;
}

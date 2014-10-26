
#include "Player.h"
#include "utilities.h"

namespace CIG
{
    Player::Player(const Player &p, Chessboard *cb)
        : makeBestMove(p.makeBestMove), chessboard(cb), index(p.index), ownedChessmans(p.ownedChessmans)
    {
    }

    Player::Player(unsigned short p, void (*makeBestMove_)(Chessboard *cb, void *)  , Chessboard *cb)
        : chessboard(cb), index(p), ownedChessmans(), makeBestMove(makeBestMove_)
    {
    }

    Player::Player(): chessboard(NULL), index((unsigned short) - 1), ownedChessmans(), makeBestMove(GUI::askForMove)
    {
    }

    Player::~Player()
    {
    }

    void Player::operator=(const Player &p)
    {
        makeBestMove = p.makeBestMove;
        chessboard = p.chessboard;
        //ownedChessmans = p.ownedChessmans;
        ownedChessmans.forceCopyFrom(p.ownedChessmans);
        index = p.index;
    }
}
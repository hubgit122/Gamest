
#include "Player.h"
#include "utilities.h"

namespace CIG
{
    Player::Player(const Player &p)
        : makeBestMove(p.makeBestMove),  index(p.index)
    {
    }

    Player::Player(unsigned short p, string(*makeBestMove_)(string))
        :  index(p), makeBestMove(makeBestMove_)
    {
    }

    Player::~Player()
    {
    }

    void Player::operator=(const Player &p)
    {
        makeBestMove = p.makeBestMove;
        index = p.index;
    }
}
#include "ChessPlayer.h"
#include "utilities.h"

namespace CIG
{
    ChessPlayer::ChessPlayer(const ChessPlayer &p, Chessboard &cb)
        : chessboard(cb), ownedChessmans(p.ownedChessmans)
    {
    }

    ChessPlayer::ChessPlayer(unsigned short p, Chessboard &cb)
        : chessboard(cb), ownedChessmans()
    {
    }

    ChessPlayer::ChessPlayer(Chessboard &cb) : chessboard(cb), ownedChessmans()
    {
    }

    ChessPlayer::~ChessPlayer()
    {
    }

    void ChessPlayer::operator=(const ChessPlayer &p)
    {
        assert(&p.chessboard == &chessboard);
        ownedChessmans.forceCopyFrom(p.ownedChessmans);        //ownedChessmans = p.ownedChessmans;
    }
}
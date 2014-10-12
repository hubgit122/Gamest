
#include "Chessman.h"

bool CIG::Chessman::onPickIntent()
{
    if(status == ChessGameConfig::ON_BOARD)
    {
        status = ChessGameConfig::OFF_BOARD;
        return true;
    }
    else
    {
        return false;
    }
}

bool CIG::Chessman::onPutIntent(PointOrVector p)
{
    if(status == ChessGameConfig::OFF_BOARD)
    {
        status = ChessGameConfig::ON_BOARD;
        coordinate = p;
        return true;
    }
    else
    {
        return false;
    }
}

bool CIG::Chessman::onCapturedIntent()
{
    if(status == ChessGameConfig::ON_BOARD)
    {
        status = ChessGameConfig::CAPTURED;
        return true;
    }
    else
    {
        return false;
    }
}

bool CIG::Chessman::onPromotionIntent(ChessGameConfig::CHESSMAN_TYPES t)
{
    chessmanType = t;
    return true;
}

bool CIG::Chessman::onCaptureIntent(Chessman *c)
{
    return true;
}

void CIG::Chessman::operator=(const Chessman &c)
{
    memcpy(this, &c, sizeof(Chessman));
}

void CIG::Chessman::undoPick()
{
    this->status = ChessGameConfig::ON_BOARD;
}

void CIG::Chessman::undoPut()
{
    this->status = ChessGameConfig::OFF_BOARD;
}

void CIG::Chessman::undoCaptured()
{
    this->status = ChessGameConfig::ON_BOARD;
}

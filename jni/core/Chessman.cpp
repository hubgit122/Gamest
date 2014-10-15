
#include "Chessman.h"

bool CIG::Chessman::onPickIntent()
{
    if(status == ON_BOARD)
    {
        status = OFF_BOARD;
        return true;
    }
    else
    {
        return false;
    }
}

bool CIG::Chessman::onPutIntent(PointOrVector p)
{
    if(status == OFF_BOARD)
    {
        status = ON_BOARD;
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
    if(status == ON_BOARD)
    {
        status = CAPTURED;
        return true;
    }
    else
    {
        return false;
    }
}

bool CIG::Chessman::onPromotionIntent(CHESSMAN_TYPES t)
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
    this->status = ON_BOARD;
}

void CIG::Chessman::undoPut()
{
    this->status = OFF_BOARD;
}

void CIG::Chessman::undoCaptured()
{
    this->status = ON_BOARD;
}


#include "ChessmanIndex.h"
namespace CIG
{
    ChessmanIndex::ChessmanIndex(void)
    {
    }

    ChessmanIndex::ChessmanIndex(const ChessmanIndex &ci): player(ci.player), index(ci.index)
    {
    }


    ChessmanIndex::ChessmanIndex(unsigned short p, unsigned short i): player(p), index(i)
    {
    }

    ChessmanIndex::~ChessmanIndex(void)
    {
    }

    void ChessmanIndex::clear()
    {
        player = (unsigned short) - 1;
        index = -1;
    }

    bool ChessmanIndex::operator==(const ChessmanIndex &ci)
    {
        return (player == ci.player) && (index == ci.index);
    }

    void ChessmanIndex::operator=(const ChessmanIndex &ci)
    {
        memcpy(this, &ci, sizeof(ChessmanIndex));
    }
}

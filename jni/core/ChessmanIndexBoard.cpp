
#include "ChessmanIndexBoard.h"

namespace CIG
{
    void CIG::ChessmanIndexBoard::operator=(const ChessmanIndexBoard &clb)
    {
        if(!content)
        {
            if((content = (ChessmanIndex *) malloc(sizeof(ChessmanIndex) << ChessGameConfig::INI_BOARD_HEIGHT_LOG2 << ChessGameConfig::INI_BOARD_WIDTH_LOG2)) == 0)
            {
                GUI::inform("������ChessmanLocaionBoardʱ�ڴ治��. ", true);
            }
        }

        memcpy(content, clb.content, sizeof(ChessmanIndex) << ChessGameConfig::INI_BOARD_HEIGHT_LOG2 << ChessGameConfig::INI_BOARD_WIDTH_LOG2);
    }

    ChessmanIndexBoard::ChessmanIndexBoard()
    {
        if((content = (ChessmanIndex *) malloc(sizeof(ChessmanIndex) << ChessGameConfig::INI_BOARD_HEIGHT_LOG2 << ChessGameConfig::INI_BOARD_WIDTH_LOG2)) == 0)
        {
            GUI::inform("������ChessmanLocaionBoardʱ�ڴ治��. ", true);
        }

        memset(content, -1, sizeof(ChessmanIndex) << ChessGameConfig::INI_BOARD_HEIGHT_LOG2 << ChessGameConfig::INI_BOARD_WIDTH_LOG2);
    }

    ChessmanIndexBoard::ChessmanIndexBoard(const ChessmanIndexBoard &clb)
    {
        if((content = (ChessmanIndex *) malloc(sizeof(ChessmanIndex) << ChessGameConfig::INI_BOARD_HEIGHT_LOG2 << ChessGameConfig::INI_BOARD_WIDTH_LOG2)) == 0)
        {
            GUI::inform("������ChessmanLocaionBoardʱ�ڴ治��. ", true);
        }

        memcpy(content, clb.content, sizeof(ChessmanIndex) << ChessGameConfig::INI_BOARD_HEIGHT_LOG2 << ChessGameConfig::INI_BOARD_WIDTH_LOG2);
    }

    ChessmanIndexBoard::~ChessmanIndexBoard()
    {
        if(content)
        {
            free(content);
        }
    }

    CIG::ChessmanIndex &ChessmanIndexBoard::operator[](PointOrVector p)
    {
        return content[(p[1] << ChessGameConfig::INI_BOARD_WIDTH_LOG2) + p[0] ];
    }
}



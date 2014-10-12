
#ifndef __CHESSMAN_LOCATION__
#define __CHESSMAN_LOCATION__

#include "utilities.h"
#include "ChessGameConfig.h"

namespace CIG
{
    class ChessmanIndex
    {
        public:
            ChessmanIndex(void);
            ChessmanIndex(PLAYER_NAMES p, int i);
            ChessmanIndex(const ChessmanIndex &ci);
            ~ChessmanIndex(void);
            void operator = (const ChessmanIndex &ci);

            PLAYER_NAMES player;
            int index;

            bool operator==(const ChessmanIndex &ci);
            void clear();
    };
}
#endif //__CHESSMAN_LOCATION__


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
            ChessmanIndex(unsigned short p, unsigned short i);
            ChessmanIndex(const ChessmanIndex &ci);
            ~ChessmanIndex(void);
            void operator = (const ChessmanIndex &ci);

            unsigned short player;
            unsigned short index;

            bool operator==(const ChessmanIndex &ci);
            void clear();

            inline virtual string toJSON()const;
    };
}
#endif //__CHESSMAN_LOCATION__

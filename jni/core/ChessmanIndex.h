
#ifndef __CHESSMAN_LOCATION__
#define __CHESSMAN_LOCATION__

#include "utilities.h"
#include "Object.h"

namespace CIG
{
    class ChessmanIndex : public Object
    {
        public:
            ChessmanIndex(const MyJSONNode &json) : JSON_INI(player), JSON_INI(index) {}
            ChessmanIndex(void) {};
            ChessmanIndex(unsigned short p, unsigned short i);
            ChessmanIndex(const ChessmanIndex &ci);
            virtual ~ChessmanIndex() {};
            void operator = (const ChessmanIndex &ci);

            unsigned short player;
            unsigned short index;

            bool operator==(const ChessmanIndex &ci);
            void clear();

            inline virtual string toJSON()const;
    };
}
#endif //__CHESSMAN_LOCATION__

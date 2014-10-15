
#ifndef __CHESSMAN_LOCATION_BOARD__
#define __CHESSMAN_LOCATION_BOARD__

#include "ChessmanIndex.h"
#include "ChessGameConfig.h"
#include "utilities.h"

namespace CIG
{
    template <class T, unsigned short INI_BOARD_WIDTH_LOG2, unsigned short INI_BOARD_HEIGHT_LOG2>
    class Board : public Array < T, 1 << INI_BOARD_WIDTH_LOG2 << INI_BOARD_HEIGHT_LOG2, -1 >
    {
        public:
            Board() : Array()
            {
                for(short i = 0; i < (1 << INI_BOARD_HEIGHT_LOG2); ++i)
                {
                    for(short j = 0; j < (1 << INI_BOARD_WIDTH_LOG2); ++j)
                    {
                        this->add(T());
                    }
                }
            };
            Board(const Board &b) : Array < T, 1 << INI_BOARD_WIDTH_LOG2 << INI_BOARD_HEIGHT_LOG2, -1 > (b) {};
            ~Board();
            inline virtual string toJSON()const;

            void operator= (const Board &b)
            {
                (Array &)(*this) = (const Array < T, 1 << INI_BOARD_WIDTH_LOG2 << INI_BOARD_HEIGHT_LOG2, -1 > &)b;
            }

            T &operator[](PointOrVector p)const
            {
                return (*this)[(p[1] << INI_BOARD_WIDTH_LOG2) + p[0]];
            }
    };
}

#endif  //__CHESSMAN_LOCATION_BOARD__
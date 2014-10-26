
#ifndef __CHESSMAN_LOCATION_BOARD__
#define __CHESSMAN_LOCATION_BOARD__

#include "ChessmanIndex.h"
#include "utilities.h"
#include "PointOrVectorS.h"

namespace CIG
{
    template <class T>
    class Board : public Array < T, 256, 0>
    {
        public:
            unsigned short INI_BOARD_WIDTH_LOG2;
            unsigned short INI_BOARD_HEIGHT_LOG2;

            Board(unsigned short INI_BOARD_WIDTH_LOG2 = 4, unsigned short INI_BOARD_HEIGHT_LOG2 = 4)
                : Array(),
                  INI_BOARD_WIDTH_LOG2(INI_BOARD_WIDTH_LOG2), INI_BOARD_HEIGHT_LOG2(INI_BOARD_HEIGHT_LOG2)
            {
                for(short i = 0; i < (1 << INI_BOARD_HEIGHT_LOG2); ++i)
                {
                    for(short j = 0; j < (1 << INI_BOARD_WIDTH_LOG2); ++j)
                    {
                        this->add(T());
                    }
                }
            };

            Board(const Board &b) : Array(b)
            {
                INI_BOARD_WIDTH_LOG2 = b.INI_BOARD_WIDTH_LOG2;
                INI_BOARD_HEIGHT_LOG2 = b.INI_BOARD_HEIGHT_LOG2;
            };

            Board(const MyJSONNode &json) :
                JSON_INI(INI_BOARD_WIDTH_LOG2), JSON_INI(INI_BOARD_HEIGHT_LOG2),
                JSON_INI(Array)
            {}

            virtual ~Board() {}

            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << JSON_OBJECT(JSON_KEYVALUE(INI_BOARD_WIDTH_LOG2) JSON_COMMA JSON_KEYVALUE(INI_BOARD_HEIGHT_LOG2) JSON_COMMA JSON_KEY(Array) << Array::toJSON());
                return oss.str();
            }

            void operator= (const Board &b)
            {
                (Array & const)(*this) = (const Array < T, 256, 0> &)b;
                INI_BOARD_WIDTH_LOG2 = b.INI_BOARD_WIDTH_LOG2;
                INI_BOARD_HEIGHT_LOG2 = b.INI_BOARD_HEIGHT_LOG2;
            }

            T &operator[](PointOrVectorS p)const
            {
                return (*this)[(p[1] << INI_BOARD_WIDTH_LOG2) + p[0]];
            }

            T &at(unsigned short y, unsigned short x)const
            {
                return (*this)[(y << INI_BOARD_WIDTH_LOG2) + x];
            }
    };
}

#endif  //__CHESSMAN_LOCATION_BOARD__

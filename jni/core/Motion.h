
#ifndef __CHESSMANMOTION_H__
#define __CHESSMANMOTION_H__

#include "Object.h"
#include "ChessGameConfig.h"
#include "Chessman.h"
#include "ChessmanIndex.h"

namespace CIG
{
    class Motion
    {
        public:
            Motion();
            Motion(const Motion &op);
            Motion(ChessmanIndex ci, unsigned short op, PointOrVectorS dist = 0, PointOrVectorS pre = 0);
            virtual ~Motion();
            void operator=(const Motion &op);
            bool operator==(const Motion &op)const;

            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << JSON_OBJECT(JSON_KEYVALUE(operation) JSON_COMMA JSON_KEYVALUE(chessmanIndex) JSON_COMMA JSON_KEYVALUE(distination) JSON_COMMA JSON_KEYVALUE(savedCoodinate));
                return oss.str();
            }

            unsigned short operation;           //操作类型
            ChessmanIndex chessmanIndex;                        //棋子所属的玩家号和在玩家手中的索引号
            PointOrVectorS distination;                              //事件的位置
            PointOrVectorS savedCoodinate;                       //为了事件的恢复, 保存初始位置
    };
}

#endif /*__CHESSMANMOTION_H_*/


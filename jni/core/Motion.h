
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

            unsigned short operation;           //��������
            ChessmanIndex chessmanIndex;                        //������������Һź���������е�������
            PointOrVectorS distination;                              //�¼���λ��
            PointOrVectorS savedCoodinate;                       //Ϊ���¼��Ļָ�, �����ʼλ��
    };
}

#endif /*__CHESSMANMOTION_H_*/


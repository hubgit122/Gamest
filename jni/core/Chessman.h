
#ifndef __CHESSMAN_H__
#define __CHESSMAN_H__

#include "utilities.h"
#include "ChessGameConfig.h"
#include "ChessmanIndex.h"
#include "Object.h"

namespace CIG
{
    class Chessman: public Object
    {
        private:
            Chessman();
        public:
            inline virtual ~Chessman() {};
            inline Chessman(const Chessman &c)
            {
                memcpy(this, &c, sizeof(Chessman));
            };
            inline Chessman(short t, const PointOrVectorS &c, unsigned short p, unsigned short index, CHESSMAN_STATUS s)
                : chessmanType(t), coordinate(c), chessmanIndex(p, index), status(s)
            {
            }
            inline Chessman(const MyJSONNode &json) : JSON_INI(chessmanType), JSON_INI(coordinate), JSON_INI(chessmanIndex), JSON_INI(status) {}
            short chessmanType;
            PointOrVectorS coordinate;
            ChessmanIndex chessmanIndex;
            CHESSMAN_STATUS status;

            void operator = (const Chessman &c);
            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << JSON_OBJECT(JSON_KEYVALUE(chessmanType) JSON_COMMA JSON_KEYVALUE(coordinate) JSON_COMMA JSON_KEYVALUE(chessmanIndex) JSON_COMMA JSON_KEYVALUE(status));
                return oss.str();
            }

            //************************************
            // Method:    onXXIntent
            // FullName:  CIG::Chessman::onIntent
            // Access:    virtual public
            // Returns:   bool
            // Qualifier:
            // Parameter: CIGConfig::Operation op, xx
            // 查询操作否可用, 并更新棋子状态.
            // 虚函数, 默认一切操作均可通过检查. 若有特殊需要, 应该重新定义.
            //************************************
            virtual bool onPickIntent();
            virtual bool onPutIntent(PointOrVectorS p);
            virtual bool onCapturedIntent();
            virtual bool onCaptureIntent(Chessman *c);
            virtual bool onPromotionIntent(short t);

            virtual void undoPick();
            virtual void undoPut();
            virtual void undoCaptured();
    };
}

#endif /*__CHESSMAN_H_*/


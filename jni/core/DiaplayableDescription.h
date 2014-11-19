#include "Object.h"
#include "PointOrVectorS.h"
#ifndef __DIAPLAYABLEDESCRIPTION_H__
#define __DIAPLAYABLEDESCRIPTION_H__

namespace CIG
{
    class DiaplayableDescription: public Object
    {
        public:
            inline DiaplayableDescription(const MyJSONNode &json) : JSON_INI(leftUp), JSON_INI(uri), JSON_INI(angle), JSON_INI(scale) {}
            virtual ~DiaplayableDescription() {};
            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << JSON_OBJECT(JSON_KEYVALUE(leftUp) JSON_COMMA JSON_KEYVALUE(uri) JSON_COMMA JSON_KEYVALUE(angle) JSON_COMMA JSON_KEYVALUE(scale));
                return oss.str();
            }
            PointOrVectorS leftUp;  //左上角
            string uri;  //图片在工程中的位置
            degree angle;  //顺时针旋转角度
            float scale;   //缩放比例
    };
}
#endif // !__DIAPLAYABLEDESCRIPTION_H__

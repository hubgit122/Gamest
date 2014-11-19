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
            PointOrVectorS leftUp;  //���Ͻ�
            string uri;  //ͼƬ�ڹ����е�λ��
            degree angle;  //˳ʱ����ת�Ƕ�
            float scale;   //���ű���
    };
}
#endif // !__DIAPLAYABLEDESCRIPTION_H__

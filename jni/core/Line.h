#ifndef __CIGLINE__
#define __CIGLINE__
#include "utilities.h"
#include "Object.h"
#include "PointOrVectorS.h"

namespace CIG
{
    class Line : public Object
    {
        public:
            PointOrVectorS p0, p1;

            inline Line(short x0, short y0, short x1, short y1) : p0(x0, y0), p1(x1, y1) {}
            inline Line(const MyJSONNode &json) : p0(json.at("p0")), p1(json.at("p1")) {}
            inline virtual ~Line() {}

            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << JSON_OBJECT(JSON_KEYVALUE(p0) JSON_COMMA JSON_KEYVALUE(p1));
                return oss.str();
            }
    };

}
#endif




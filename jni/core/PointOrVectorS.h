#ifndef __POINT_OR_VECTORUS__
#define __POINT_OR_VECTORUS__
#include "utilities.h"
#include "Object.h"
#include "MyJSONNode.h"
#include "PointOrVector.h"

namespace CIG
{
    class PointOrVectorS: public PointOrVector<short>
    {
        public:
            PointOrVectorS()
            {
                memset(x, -1, sizeof(unsigned short) << 1);
            }

            PointOrVectorS(short x, short y) : PointOrVector(x, y)
            {
            }

            PointOrVectorS(unsigned xy)
            {
                *(unsigned *)(this->x) = xy;
            }

            PointOrVectorS(const MyJSONNode &json) : PointOrVector(json) {}

            bool operator==(const PointOrVectorS &p)const
            {
                return (*(unsigned *)this->x == *(unsigned *)(p.x));
            }

            bool operator!=(const PointOrVectorS &p)const
            {
                return !(*this == p);
            }
    };
}
#endif
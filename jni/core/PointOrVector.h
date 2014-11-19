#ifndef __POINT_OR_VECTOR_T__
#define __POINT_OR_VECTOR_T__

#include "utilities.h"
#include "Object.h"

namespace CIG
{
    template<class T>
    class PointOrVector : public Object
    {
        public:
            T x[2];

            PointOrVector()
            {
                this->x[0] = 0;
                this->x[1] = 0;
            }

            PointOrVector(T x, T y)
            {
                this->x[0] = x;
                this->x[1] = y;
            }

            PointOrVector(const MyJSONNode &json)
            {
                try
                {
                    MyJSONNode::const_iterator it = json.begin();
                    x[0] = T(MyJSONNode(*it));
                    it++;
                    x[1] = T(MyJSONNode(*it));
                }
                catch(std::exception *e)
                {
                    informError(e->what());
                    return;
                }
            }

            T operator*(const PointOrVector &p)
            {
                return x[0] * p.x[0] + x[1] * p.x[1];
            }

            void operator = (const PointOrVector &p)
            {
                memcpy(x, p.x, sizeof(T) << 1);
            }

            friend PointOrVector operator*(T lambda, const PointOrVector &p)
            {
                PointOrVector temp = p;

                temp.x[0] *= lambda;
                temp.x[1] *= lambda;

                return temp;
            }

            PointOrVector operator- (const PointOrVector &p)
            {
                PointOrVector temp = *this;

                temp.x[0] -= p.x[0];
                temp.x[1] -= p.x[1];

                return temp;
            }

            PointOrVector operator+ (const PointOrVector &p)
            {
                PointOrVector temp = *this;

                temp.x[0] += p.x[0];
                temp.x[1] += p.x[1];

                return temp;
            }

            T &operator [](unsigned i)
            {
                assert(i < 2);
                return x[i];
            }

            inline virtual string toJSON()
            {
                ostringstream oss;
                oss << JSON_ARRAY(JSON_VALUE(x[0]) JSON_COMMA JSON_VALUE(x[1]));
                return oss.str();
            }
    };
}
#endif
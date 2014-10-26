#ifndef __MY_JSON_NODE__
#define __MY_JSON_NODE__
#include "..\libjson\_internal\Source\JSONNode.h"
#include <string>
#include "types.h"
using namespace std;
namespace CIG
{
    class MyJSONNode : public JSONNode
    {
        public:
            MyJSONNode(const JSONNode &j) : JSONNode(j)
            {
            };
            virtual ~MyJSONNode() {};

            operator GAME_TYPE()const
            {
                return (GAME_TYPE)as_int();
            }

            operator bool()const
            {
                return as_bool();
            }

            operator unsigned() const
            {
                return as_int();
            }

            operator short()const
            {
                return as_int();
            }
            operator unsigned short()const
            {
                return as_int();
            }
            operator double()const
            {
                return (double)as_float();
            }

            operator float()const
            {
                return as_float();
            }

            operator int()const
            {
                return as_int();
            }
            operator string()const
            {
                return as_string();
            }

            const MyJSONNode at(string s)const
            {
                return JSONNode::at(s);
            }
        private:

    };
}
#endif //__MY_JSON_NODE__
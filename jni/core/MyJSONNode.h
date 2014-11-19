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

            inline operator CHESSMAN_STATUS()const
            {
                return (CHESSMAN_STATUS)as_int();
            }
            inline operator GAME_TYPE()const
            {
                return (GAME_TYPE)as_int();
            }

            inline operator bool()const
            {
                return as_bool();
            }

            inline operator unsigned long()const
            {
                return as_int();
            }

            inline operator unsigned() const
            {
                return as_int();
            }

            inline operator short()const
            {
                return as_int();
            }
            inline operator unsigned short()const
            {
                return as_int();
            }
            inline operator double()const
            {
                return (double)as_float();
            }

            inline operator float()const
            {
                return as_float();
            }

            inline operator int()const
            {
                return as_int();
            }
            inline operator string()const
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
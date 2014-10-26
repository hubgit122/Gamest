#ifndef __OPERATION_H__
#define __OPERATION_H__
#include <string>
#include "Object.h"

namespace CIG
{
    class Operation : public Object
    {
        public:
            string name;
            short id;

            inline Operation(string s, unsigned short i) : name(s), id(i) {}
            inline Operation(const MyJSONNode &json) : JSON_INI(name), JSON_INI(id) {}
            inline virtual ~Operation() {}

            operator short()const
            {
                return id;
            }

            bool operator ==(const Operation &op)
            {
                return id == op.id;
            }
            bool operator !=(const Operation &op)
            {
                return id != op.id;
            }
            //bool operator==(const short s)
            //{
            //    return id == s;
            //}
            //bool operator!=(const short s)
            //{
            //    return id != s;
            //}

            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << JSON_OBJECT(JSON_KEYVALUE(name) JSON_COMMA JSON_KEYVALUE(id));
                return oss.str();
            }

        private:
            Operation() {}
    };
}
#endif//__OPERATION_H__
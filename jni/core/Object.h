#ifndef __CIGOBJECT_H__
#define __CIGOBJECT_H__

#include "utilities.h"
/*************************************************************************
  ����������ϵͳ�������Ļ���, ���������������ͳ�Ա�ĸ���.
  Ҫ�������ַ����������ڳ��ڸ���.
**************************************************************************/
namespace CIG
{
    class Object
    {
        public:
            inline Object() {};
            inline Object(const MyJSONNode &json) {}
            inline Object(const Object &o) {};
            inline virtual ~Object() {};
            static ostringstream errors;

            inline virtual void assert(bool b, string msg = "")const
            {
                if(!b)
                {
                    informError(msg);
                }
            }

            inline virtual void *memoryAlloc(unsigned size)
            {
                void *tmp;

                if(tmp = malloc(size))
                {
                    return tmp;
                }
                else
                {
                    informError("unsufficent memory!");
                }
            }

            inline virtual void informError(const string &str)const
            {
                errors << "*******************error***************\n" << str << endl;
                ostringstream oss;
                oss << *this;
                errors << "error in " << oss.str() << endl;
            }

            inline virtual string toJSON()const
            {
                return "{}";
            }

            friend ostream &operator << (ostream &os, const Object &o)
            {
                ostringstream oss;
                oss << o;
                os << oss.str();
                return os;
            }

            friend ostringstream &operator<<(ostringstream &oss, const Object &o)
            {
                oss << o.toJSON();
                return oss;
            }
    };
}
#endif /*__CIGOBJECT_H_*/


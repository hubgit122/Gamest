#include "..\..\Object.h"

namespace CIG
{
    class stringJSON : public string, public Object
    {
        public:
            stringJSON() {};
            stringJSON(const string &s) : string(s) {}
            stringJSON(const MyJSONNode &json) : string(json.as_string()) {}

            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << "\"" << *this << "\"";
                return oss.str();
            }
            inline virtual ~stringJSON() {};

        private:

    };
}
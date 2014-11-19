#ifndef __Vector_JSON__
#define __Vector_JSON__
#include <vector>
using namespace std;

namespace CIG
{
    template<class T>
    class VectorJSON : public vector<T>, public Object
    {
        public:
            VectorJSON() {}
            VectorJSON(const vector &v) : vector(v) {}
            VectorJSON(const VectorJSON &v) : Object(v), vector(v) {}
            VectorJSON(const MyJSONNode &json)
            {
                try
                {
                    JSONNode::const_iterator it = json.begin();

                    while(it != json.end())
                    {
                        MyJSONNode k(*it);
                        this->push_back(T(k));
                        it++;
                    }
                }
                catch(std::out_of_range *e)
                {
                    return;
                }
            }

            inline virtual ~VectorJSON() {}

            typename vector<T>::const_iterator find(const T &val)const
            {
                for(vector::const_iterator it = this->begin(); it != this->end(); ++it)
                {
                    if(*it == val)
                    {
                        return it;
                    }
                }

                return this->end();
            }

            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << "[";

                for(vector::const_iterator i = this->begin(); i != this->end();)
                {
                    oss << (typeid(T) == typeid(string) ? "\"" : "") << (*i) << (typeid(T) == typeid(string) ? "\"" : "");
                    ++i;

                    if(i != this->end())
                    {
                        oss << ",";
                    }
                    else
                    {
                        break;
                    }
                }

                oss << "]";
                return oss.str();
            }
    };
}
#endif//__Vector_JSON__

#ifndef __List_JSON__
#define __List_JSON__
#include <list>
using namespace std;

namespace CIG
{
    template<class T>
    class ListJSON : public list<T>, public Object
    {
        public:
            ListJSON(const list &l) : list(l) {}
            ListJSON(const MyJSONNode &json)
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

            inline virtual ~ListJSON() {}
            inline T &operator[](const int index)
            {
                if(size() == 0)
                {
                    return (T &)( * 0);
                }

                if(index >= this->size())
                {
                    return this->back();
                }
                else if(index < 0)
                {
                    return this->front();
                }
                else
                {
                    for(list::const_iterator it = this->begin(); it != this->end(); ++it)
                    {
                        if(index-- == 0)
                        {
                            return *it;
                        }
                    }
                }
            }
            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << "[";

                for(list::const_iterator i = this->begin(); i != this->end();)
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
#endif//__List_JSON__
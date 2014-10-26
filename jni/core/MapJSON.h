#ifndef __MAP_JSON__
#define __MAP_JSON__
namespace CIG
{
    template<class K, class V>
    class MapJSON : public map<K, V>, public Object
    {
        public:
            MapJSON(const map &m) : map(m) {}
            MapJSON(const MyJSONNode &json)
            {
                try
                {
                    const JSONNode &keys(json.at("keys"));
                    const JSONNode &values(json.at("values"));
                    JSONNode::const_iterator itk = keys.begin();
                    JSONNode::const_iterator itv = values.begin();

                    while(itk != keys.end())
                    {
                        MyJSONNode k(*itk), v(*itv);
                        map::insert(pair<K, V>(K(k), V(v)));
                        itk++;
                        itv++;
                    }
                }
                catch(std::out_of_range *e)
                {
                    return;
                }
            }
            inline virtual ~MapJSON() {}

            inline virtual string toJSON()const
            {
                ostringstream ossk, ossv;
                ossk << "\"keys\":[";
                ossv << "\"values\":[";
                map::const_iterator it = this->begin();

                while(it != this->end())
                {
                    ossk << (typeid(K) == typeid(string) ? "\"" : "") << it->first << (typeid(K) == typeid(string) ? "\"" : "");
                    ossv << (typeid(V) == typeid(string) ? "\"" : "") << it->second << (typeid(V) == typeid(string) ? "\"" : "");

                    it++;

                    if(it != this->end())
                    {
                        ossk << ",";
                        ossv << ",";
                    }
                    else
                    {
                        break;
                    }
                }

                ossk << "]";
                ossv << "]";
                return "{" + ossk.str() + "," + ossv.str() + "}";
            }
    };
}
#endif//__MAP_JSON__

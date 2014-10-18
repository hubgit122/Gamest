#ifndef __JSON_MAP__
#define __JSON_MAP__
template<class K, class V>
class jsonMap : class map<K,V>
{
    jsonMap(const JSONNode& json)
    {
        try
        {
            JSONNode::const_iterator it = json.begin();

            while(it != json.end())
            {
                this->add(pair<K,V>(it->name()));
            }
        }
        catch(std::out_of_range *e)
        {
            return;
        }
    }
};
#endif

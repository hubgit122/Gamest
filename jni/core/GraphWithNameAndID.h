#include "Graph.h"
#ifndef __GRAPH_WITH_NAME_AND_ID__
#define __GRAPH_WITH_NAME_AND_ID__
namespace CIG
{
    //一个图, 节点有name和id两个属性, 从string name二维数组构造图, 并按次序分配short id, 返回id的二维数组作为id图. 为了运行更快.
    //要求T有name, id构造函数.
    class GraphWithNameAndID : public Graph<short>
    {
        public:
            VectorJSON<string> names;
            GraphWithNameAndID() {}
            GraphWithNameAndID(const vector<string> &nodes) : Graph()
            {
                for(vector<string>::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
                {
                    if(addName(*it))
                    {
                        Graph::addNode(names.size() - 1);
                    }
                }
            }
            GraphWithNameAndID(const MyJSONNode &json) : Graph(json.at("idGraph")), JSON_INI(names) {}
            inline virtual ~GraphWithNameAndID() {}
            inline virtual string toJSON()const
            {
                ostringstream oss;
                oss << JSON_OBJECT( << (const Graph &)(*this) JSON_COMMA JSON_KEYVALUE(names));
                return oss.str();
            }

            bool addName(const string &name)
            {
                if(names.find(name) == names.end())
                {
                    names.push_back(name);
                    return true;
                }

                return false;
            }
            void addEdge(const short &u, const short &v)   //u->v
            {
                assert(u < names.size());
                (*this)[u].push_back(v);
            }
    };
}
#endif//__GRAPH_WITH_NAME_AND_ID__
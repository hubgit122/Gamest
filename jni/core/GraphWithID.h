#include "Graph.h"
#ifndef __GRAPH_WITH_ID__
#define __GRAPH_WITH_ID__
namespace CIG
{
    template<class T>
    class GraphWithID : public Graph<T>
    {
        public:
            //有id的图，方便查找边。要求元素一定要有id属性，而且id一定要在图中注册过，从0开始计数。
            GraphWithID(): Graph() {}
            GraphWithID(const vector<T> &nodes) : Graph(nodes) {}
            GraphWithID(const MyJSONNode &json) : Graph(json) {}

            void addEdge(const T &u, const T &v)   //u->v
            {
                assert(u.id < g.size());
                g[u.id].push_back(v);
            }
    };
}
#endif//__GRAPH_WITH_ID__
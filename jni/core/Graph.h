#include <vector>
#include <list>
#ifndef __GRAPH_H__
#define __GRAPH_H__
namespace CIG
{
    //邻接表表示的图
    template<class T>
    class Graph: public Object
    {
    public:
        vector<list<T>> g;
        Graph(){}
        Graph(const vector<T>& nodes)
        {
            for (int i=0; i<nodes.size(); ++i)
            {
                g[i].push_front(nodes[i]);
            }
        }

        void addNode(const T& t)
        {
            g.push_back(t);
        }
        
        void addEdge(const T&u, const T&v)     //u->v
        {
            for (int i=0; i<g.size(); ++i)
            {
                if (g[i].front()==u)
                {
                    g[i].push_back(v);
                    break;
                }
            }
        }
    };
}
#endif
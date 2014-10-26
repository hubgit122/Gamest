#include "ListJSON.h"
#include "VectorJSON.h"
#include "MyJSONNode.h"
#ifndef __GRAPH_H__
#define __GRAPH_H__
namespace CIG
{
    //邻接表表示的图
    template<class T>
    class Graph : public VectorJSON<ListJSON<T>>
    {
        public:
            Graph(const MyJSONNode &json) : VectorJSON<ListJSON<T>>(json) {}
            Graph(const vector<T> &nodes)
            {
                for(int i = 0; i < nodes.size(); ++i)
                {
                    (*this)[i].push_front(nodes[i]);
                }
            }

            void addNode(const T &t)
            {
                ListJSON<T> l;
                l.push_back(t);
                (*this).push_back(l);
            }

            void addEdge(const T &u, const T &v)   //u->v
            {
                for(int i = 0; i < (*this).size(); ++i)
                {
                    if((*this)[i].front() == u)
                    {
                        (*this)[i].push_back(v);
                        break;
                    }
                }
            }
    };
}
#endif
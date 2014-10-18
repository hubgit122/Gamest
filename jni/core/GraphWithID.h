#ifndef __GRAPH_WITH_ID__
#define __GRAPH_WITH_ID__
template<class T>
class GraphWithID : public Graph<T>
{
    //��id��ͼ��������ұߡ�Ҫ��Ԫ��һ��Ҫ��id���ԣ�����idһ��Ҫ��ͼ��ע�������0��ʼ������
    GraphWithID():Graph(){}
    GraphWithID(const vector<T>& nodes) : Graph(nodes){}

    void addEdge(const T&u, const T&v)     //u->v
    {
        assert(u.id<g.size());
        g[u.id].push_back(v);
    }
};
#endif//__GRAPH_WITH_ID__
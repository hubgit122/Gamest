
#include "utilities.h"

int roundInt(float f)
{
    return int(f + 0.5);
}

template<class T>
void QuickSort(T a[], unsigned n)
{
    QuickSort(a, 0, n - 1);
}

template<class T>
void QuickSort(T a[])
{
    int n = sizeof(a) / sizeof(a[0]);
    QuickSort(a, 0, n - 1);
}

template<class T>
void QuickSort(T a[], int p, int r)
{
    if(p < r)
    {
        int q = Partition(a, p, r);
        QuickSort(a, p, q - 1);
        QuickSort(a, q + 1, r);
    }
}
template<class T>
int Partition(T a[], int p, int r)
{
    int i = p, j = r + 1;
    T x = a[p];

    while(true)
    {
        while(i < r && a[++i] < x)
            ;

        while(j > 0 && a[--j] > x)
            ;

        if(i >= j)
        {
            break;
        }

        Swap(a[i], a[j]);
    }

    a[p] = a[j];
    a[j] = x;
    return j;
}
template<class T>
inline void Swap(T &s, T &t)
{
    T temp = s;
    s = t;
    t = temp;
}

void parseBoolArray(const MyJSONNode &json, const string &s, vector<bool>& v)
{
    try
    {
        const JSONNode &a = json.at(s);
        JSONNode::const_iterator it = a.begin();
        int j = 0;

        while(it != a.end())
        {
            v.push_back((it++)->as_bool());
        }
    }
    catch(std::out_of_range *e)
    {
        return;
    }
}

void parseIntArray(const MyJSONNode &json, const string &s, vector<int>& v)
{
    try
    {
        const JSONNode &a = json.at(s);
        JSONNode::const_iterator it = a.begin();

        while(it != a.end())
        {
            v.push_back((it++)->as_int());
        }
    }
    catch(std::out_of_range *e)
    {
        return;
    }
}
